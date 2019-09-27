#include "flite/regex/regex.hpp"

#include "flite/utils/alloc.hpp"

#include "./regex_defs.hpp"

/* For access by const models */
extern const cst_regex* const cst_regex_table[] = {
    &cst_rx_dotted_abbrev_rx};

static char* regularize(const char* unregex, int match);

void cst_regex_init()
{
    /* no need to initialize regexes anymore, they are pre-compiled */

    return;
}

int cst_regex_match(const cst_regex* r, const char* str)
{
    cst_regstate* s;

    if (r == NULL) return 0;
    s = hs_regexec(r, str);
    if (s) {
        cst_free(s);
        return 1;
    }
    else
        return 0;
}

cst_regstate* cst_regex_match_return(const cst_regex* r, const char* str)
{
    if (r == NULL)
        return 0;

    return hs_regexec(r, str);
}

cst_regex* new_cst_regex(const char* str)
{
    cst_regex* r;
    char* reg_str = regularize(str, 1);

    r = hs_regcomp(reg_str);
    cst_free(reg_str);

    return r;
}

void delete_cst_regex(cst_regex* r)
{
    if (r)
        hs_regdelete(r);

    return;
}

/* These define the different escape conventions for the FSF's */
/* regexp code and Henry Spencer's */

static const char* const fsf_magic = "^$*+?[].\\";
static const char* const fsf_magic_backslashed = "()|<>";
static const char* const spencer_magic = "^$*+?[].()|\\\n";
static const char* const spencer_magic_backslashed = "<>";

/* Adaptation of rjc's mapping of fsf format to henry spencer's format */
/* of escape sequences, as taken from EST_Regex.cc in EST              */
static char* regularize(const char* unregex, int match)
{
    char* reg = cst_alloc(char, cst_strlen(unregex) * 2 + 3);
    char* r = reg;
    const char* e;
    int magic = 0, last_was_bs = 0;
    const char* in_brackets = NULL;
    const char* ex = (unregex ? unregex : "");

    if (match && *ex != '^')
        *(r++) = '^';

    for (e = ex; *e; e++) {
        if (*e == '\\' && !last_was_bs) {
            last_was_bs = 1;
            continue;
        }

        magic = strchr((last_was_bs ? fsf_magic_backslashed : fsf_magic), *e) != NULL;

        if (in_brackets) {
            *(r++) = *e;
            if (*e == ']' && (e - in_brackets) > 1)
                in_brackets = 0;
        }
        else if (magic) {
            if (strchr(spencer_magic_backslashed, *e))
                *(r++) = '\\';

            *(r++) = *e;
            if (*e == '[')
                in_brackets = e;
        }
        else {
            if (strchr(spencer_magic, *e))
                *(r++) = '\\';

            *(r++) = *e;
        }
        last_was_bs = 0;
    }

    if (match && (e == ex || *(e - 1) != '$')) {
        if (last_was_bs)
            *(r++) = '\\';
        *(r++) = '$';
    }

    *r = '\0';

    return reg;
}
