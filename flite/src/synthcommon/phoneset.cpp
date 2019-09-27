#include "flite/synthcommon/phoneset.hpp"

#include "flite/hrg/item.hpp"
#include "flite/hrg/utterance.hpp"
#include "flite/utils/val.hpp"

CST_VAL_REGISTER_TYPE_NODEL(phoneset, cst_phoneset)

cst_phoneset* new_phoneset()
{
    /* These aren't going to be supported dynamically */
    cst_phoneset* v = cst_alloc(struct cst_phoneset_struct, 1);

    v->freeable = 1;
    return v;
}

void delete_phoneset(const cst_phoneset* v)
{
    int i;

    if (v && v->freeable) {
        for (i = 0; v->featnames[i]; i++)
            cst_free((void*)v->featnames[i]);
        cst_free((void*)v->featnames);
        for (i = 0; v->featvals[i]; i++)
            delete_val((cst_val*)(void*)v->featvals[i]);
        cst_free((void*)v->featvals);
        for (i = 0; v->phonenames[i]; i++)
            cst_free((void*)v->phonenames[i]);
        cst_free((void*)v->phonenames);
        cst_free((void*)v->silence);
        for (i = 0; v->fvtable[i]; i++)
            cst_free((void*)v->fvtable[i]);
        cst_free((void*)v->fvtable);
        cst_free((void*)v);
    }
}

int phone_id(const cst_phoneset* ps, const char* phonename)
{
    int i;

    for (i = 0; i < ps->num_phones; i++)
        if (cst_streq(ps->phonenames[i], phonename))
            return i;
    /* Wonder if I should print an error here or not */
    /* printf("awb_debug cst_phoneset.c phone_id unknown phone %s\n",phonename); */

    return 0;
}

int phone_feat_id(const cst_phoneset* ps, const char* featname)
{
    int i;

    for (i = 0; ps->featnames[i]; i++)
        if (cst_streq(ps->featnames[i], featname))
            return i;

    /* Wonder if I should print an error here or not */
    return 0;
}

const cst_val* phone_feature(const cst_phoneset* ps, const char* phonename, const char* featname)
{
    return ps->featvals[ps->fvtable[phone_id(ps, phonename)]
                                   [phone_feat_id(ps, featname)]];
}

const char* phone_feature_string(const cst_phoneset* ps, const char* phonename, const char* featname)
{
    return val_string(phone_feature(ps, phonename, featname));
}

const cst_phoneset* item_phoneset(const cst_item* p)
{
    return val_phoneset(feat_val(item_utt(p)->features, "phoneset"));
}
