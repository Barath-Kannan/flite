#include "./grapheme_lex.hpp"

#include "flite/flite.hpp"
#include "flite/synth/ffeatures.hpp"
#include "flite/synth/voice.hpp"
#include "flite/utils/val.hpp"

static int cst_find_u2sampa(char* ord)
{
    int i;

    /* Now this is inefficient ... */
    for (i = 0; i < num_unicode_sampa_mapping; i++)
        if (cst_streq(ord, unicode_sampa_mapping[i][0]))
            return i;
    return -1;
}

static int cst_utf8_as_hex(const char* in, char* out)
{
    int o;

    o = cst_utf8_ord_string(in);
    if ((o > 96) && (o < 123)) {
        cst_sprintf(out, "let_%c", (unsigned char)o);
    }
    else if ((o > 64) && (o < 91)) { /* Map uppercase to lowercase */
        cst_sprintf(out, "let_%c", (unsigned char)o + 32);
    }
    else
        cst_sprintf(out, "u%04Xp", o);
    return o;
}

cst_val* cmu_grapheme_lex_lts_function(const struct lexicon_struct* l, const char* word, const char* pos, const cst_features* feats)
{
    cst_val* phones = 0;
    cst_val* utflets = 0;
    const cst_val* v;
    char ord[10];
    int i, phindex;

    /* string to utf8 chars */
    utflets = cst_utf8_explode(word);

    for (v = utflets; v; v = val_cdr(v)) {
        /* We will add the found phones in reverse order and reverse then */
        /* afterwards */
        cst_utf8_as_hex(val_string(val_car(v)), ord);
        phindex = cst_find_u2sampa(ord);
        printf("awb_debug lookup sampa %s %s\n", val_string(val_car(v)), ord);
#if 0        
        if (phindex < 0)
            printf("awb_debug no sampa %s %s\n",val_string(val_car(v)),ord);
#endif
        for (i = 4; (phindex >= 0) && (i > 0); i--) {
            if (unicode_sampa_mapping[phindex][i])
                phones = cons_val(string_val(unicode_sampa_mapping[phindex][i]), phones);
        }
    }

    phones = val_reverse(phones);
#if 0
    printf("cmu_grapheme_lex.c: word \"%s\" ",word);
    val_print(stdout,phones);
    printf("\n");
#endif

    delete_val(utflets);

    return phones;
}

cst_utterance* cmu_grapheme_postlex(cst_utterance* u)
{
    return u;
}

static int cmu_grapheme_is_vowel(const char* p)
{
    /* This a place holder, we know its sampa, so I should look it up */
    /* in the list, not guess from typographical conventions          */
    if (strchr("aeiouAEIOU", p[0]) == NULL)
        return FALSE;
    else
        return TRUE;
}

static int cmu_grapheme_contains_vowel(const cst_val* r)
{
    const cst_val* x;

    for (x = r; x; x = val_cdr(x)) {
        if (cmu_grapheme_is_vowel(val_string(val_car(x))))
            return TRUE;
    }

    return FALSE;
}

static int cmu_grapheme_has_vowel_in_syl(const cst_item* i)
{
    const cst_item* n;

    for (n = i; n; n = item_prev(n))
        if (cmu_grapheme_is_vowel(ffeature_string(n, "name")))
            return TRUE;
    return FALSE;
}

int cmu_grapheme_syl_boundary(const cst_item* i, const cst_val* rest)
{
    if (!rest)
        return TRUE;
    else if (!cmu_grapheme_contains_vowel(rest))
        return FALSE;
    else if (!cmu_grapheme_has_vowel_in_syl(i))
        return FALSE;
#if 0
    else if (rest && val_cdr(rest) &&
             cst_streq("n",val_string(val_car(rest))) &&
             !cmu_grapheme_is_vowel(val_string(val_car(rest))))
        return FALSE;
    else if (rest && val_cdr(rest) &&
             cmu_grapheme_is_vowel(ffeature_string(i,"name")) &&
             !cmu_grapheme_is_vowel(val_string(val_car(rest))) &&
             !cmu_grapheme_is_vowel(val_string(val_car(val_cdr(rest)))))
        return FALSE;
    else if (rest && val_cdr(rest) && val_cdr(val_cdr(rest)) &&
             !cmu_grapheme_is_vowel(val_string(val_car(rest))) &&
             !cmu_grapheme_is_vowel(val_string(val_car(val_cdr(rest)))) &&
             !cmu_grapheme_is_vowel(val_string(val_car(val_cdr(val_cdr(rest))))))
        return FALSE;
    else if (rest && val_cdr(rest) &&
             (cst_streq(val_string(val_car(rest)),
                        val_string(val_car(val_cdr(rest))))))
        return FALSE;
#endif
    else
        return TRUE;
}

cst_lexicon cmu_grapheme_lex;

cst_lexicon* cmu_grapheme_lex_init(void)
{
    /* Should it be global const or dynamic */
    /* Can make lts_rules just a cart tree like others */
    cst_lexicon* l;

    if (cmu_grapheme_lex.lts_function)
        return &cmu_grapheme_lex;

    l = &cmu_grapheme_lex;
    l->name = cst_strdup("cmu_grapheme_lex");

    l->lts_function = cmu_grapheme_lex_lts_function;
    l->syl_boundary = cmu_grapheme_syl_boundary;
    l->postlex = cmu_grapheme_postlex;

    return l;
}
