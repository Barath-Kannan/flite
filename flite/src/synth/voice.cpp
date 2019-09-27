#include "flite/synth/voice.hpp"

#include "flite/utils/alloc.hpp"
#include "flite/utils/features.hpp"
#include "flite/wavesynth/clunits.hpp"

CST_VAL_REGISTER_TYPE(voice, cst_voice)

cst_voice* new_voice()
{
    cst_voice* v = cst_alloc(struct cst_voice_struct, 1);

    v->features = new_features();
    v->ffunctions = new_features();

    return v;
}

void delete_voice(cst_voice* v)
{
    if (v) {
        if (feat_present(v->features, "voxdata")) {
            if (feat_present(v->features, "clunit_db"))
                flite_munmap_clunit_voxdata(v);
        }

        delete_features(v->features);
        delete_features(v->ffunctions);
        cst_free(v);
    }
}

int flite_mmap_clunit_voxdata(const char* voxdir, cst_voice* voice)
{
    /* Map clunit_db in voice data for giveb voice */
    char* path;
    const char* name;
    const char* x;
    int* indexes;
    cst_filemap* vd;
    cst_clunit_db* clunit_db;
    int i;

    name = get_param_string(voice->features, "name", "voice");
    path = cst_alloc(char, cst_strlen(voxdir) + 1 + cst_strlen(name) + 1 + cst_strlen("voxdata") + 1);
    cst_sprintf(path, "%s/%s.voxdata", voxdir, name);

    vd = cst_mmap_file(path);

    feat_set_string(voice->features, "voxdir", path);
    cst_free(path);

    if (vd == NULL)
        return -1;

    x = (const char*)vd->mem;
    if (!cst_streq("CMUFLITE", x)) { /* Not a Flite voice data file */
        cst_munmap_file(vd);
        return -1;
    }

    for (i = 9; x[i] && i < 64; i++)
        if (x[i] != ' ')
            break;

    if (!cst_streq(name, &x[i])) { /* Not a voice data file for this voice */
        cst_munmap_file(vd);
        return -1;
    }

    /* This uses a hack to put in a void pointer to the cst_filemap */
    feat_set(voice->features, "voxdata", userdata_val(vd));
    indexes = (int*)&x[64];

    clunit_db = val_clunit_db(feat_val(voice->features, "clunit_db"));

    clunit_db->sts->resoffs =
        (const unsigned int*)&x[64 + 20];
    clunit_db->sts->frames =
        (const unsigned short*)&x[64 + 20 + indexes[0]];
    clunit_db->mcep->frames =
        (const unsigned short*)&x[64 + 20 + indexes[0] + indexes[1]];
    clunit_db->sts->residuals =
        (const unsigned char*)&x[64 + 20 + indexes[0] + indexes[1] + indexes[2]];
    clunit_db->sts->ressizes =
        (const unsigned char*)&x[64 + 20 + indexes[0] + indexes[1] + indexes[2] + indexes[3]];

    return 0;
}

int flite_munmap_clunit_voxdata(cst_voice* voice)
{
    cst_filemap* vd;
    const cst_val* val_vd;
    const cst_val* val_clunit_database;
    cst_clunit_db* clunit_db;

    val_vd = get_param_val(voice->features, "voxdata", NULL);
    val_clunit_database = get_param_val(voice->features, "clunit_db", NULL);

    if (val_vd && val_clunit_database) {
        clunit_db = val_clunit_db(val_clunit_database);
        clunit_db->sts->resoffs = NULL;
        clunit_db->sts->frames = NULL;
        clunit_db->mcep->frames = NULL;
        clunit_db->sts->residuals = NULL;
        clunit_db->sts->ressizes = NULL;
        vd = (cst_filemap*)val_userdata(val_vd);
        cst_munmap_file(vd);
    }

    return 0;
}
