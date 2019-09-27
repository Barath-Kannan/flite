#include "flite/wavesynth/diphone.hpp"
#include "flite/wavesynth/sigpr.hpp"
#include "flite/wavesynth/units.hpp"

#include "flite/hrg/hrg.hpp"
#include "flite/synthcommon/track.hpp"
#include "flite/synthcommon/utt_utils.hpp"
#include "flite/synthcommon/wave.hpp"
#include "flite/utils/math.hpp"

CST_VAL_REGISTER_TYPE_NODEL(diphone_db, cst_diphone_db)

static int get_diphone_entry(cst_diphone_db* udb, const char* name);
static int get_diphone_entry_bsearch(const cst_diphone_entry* entries, int start, int end, const char* key);

cst_utterance* diphone_synth(cst_utterance* utt)
{
    get_diphone_units(utt);
    join_units(utt);
    return utt;
}

cst_utterance* get_diphone_units(cst_utterance* utt)
{
    /* Select units from db with times etc */
    cst_relation* units;
    cst_item *s0, *s1, *u;
    float end0, end1;
    char diphone_name[22];
    cst_diphone_db* udb;
    int unit_entry = -1;

    udb = val_diphone_db(utt_feat_val(utt, "diphone_db"));
    utt_set_feat(utt, "sts_list", sts_list_val(udb->sts));

    units = utt_relation_create(utt, "Unit");

    for (s0 = relation_head(utt_relation(utt, "Segment"));
         s0 && item_next(s0);
         s0 = s1) {
        s1 = item_next(s0);
        unit_entry = -1;
        if (cst_streq("-", ffeature_string(s0, "ph_vc")) &&
            cst_streq("-", ffeature_string(s0, "R:SylStructure.n.ph_vc"))) { /* Might have consonant cluster diphones */
            cst_sprintf(diphone_name, "%.10s_-_%.10s", item_name(s0), item_name(s1));
            unit_entry = get_diphone_entry(udb, diphone_name);
        }

        if (unit_entry == -1) /* no consonant cluster diphone */
        {
            cst_sprintf(diphone_name, "%.10s-%.10s", item_name(s0), item_name(s1));

            unit_entry = get_diphone_entry(udb, diphone_name);
        }

        if (unit_entry == -1) {
            cst_errmsg("flite: udb failed to find entry for: %s\n", diphone_name);
            unit_entry = 0;
        }

        /* first half of diphone */
        u = relation_append(units, NULL);
        item_add_daughter(s0, u);
        item_set_string(u, "name", diphone_name);
        end0 = item_feat_float(s0, "end");
        item_set_int(u, "target_end", (int)(end0 * udb->sts->sample_rate));
        item_set_int(u, "unit_entry", unit_entry);
        item_set_int(u, "unit_start", udb->diphones[unit_entry].start_pm);
        item_set_int(u, "unit_end", udb->diphones[unit_entry].start_pm + udb->diphones[unit_entry].pb_pm);
        /* second half of diphone */
        u = relation_append(units, NULL);
        item_add_daughter(s1, u);
        item_set_string(u, "name", diphone_name);
        end1 = item_feat_float(s1, "end");
        item_set_int(u, "target_end", (int)(((end0 + end1) / 2.0) * udb->sts->sample_rate));
        item_set_int(u, "unit_entry", unit_entry);
        item_set_int(u, "unit_start", udb->diphones[unit_entry].start_pm + udb->diphones[unit_entry].pb_pm);
        item_set_int(u, "unit_end", udb->diphones[unit_entry].start_pm + udb->diphones[unit_entry].pb_pm + udb->diphones[unit_entry].end_pm);
    }

    return utt;
}

static int get_diphone_entry(cst_diphone_db* udb, const char* name)
{
    return get_diphone_entry_bsearch(udb->diphones, 0, udb->num_entries, name);
}

static int get_diphone_entry_bsearch(const cst_diphone_entry* entries, int start, int end, const char* key)
{
    int mid, c;

    while (start < end) {
        mid = (start + end) / 2;

        c = strcmp(entries[mid].name, key);

        if (c == 0)
            return mid;
        else if (c > 0)
            end = mid;
        else
            start = mid + 1;
    }

    return -1; /* can't find it */
}
