#include "flite/regex/regex.hpp"

#include "flite/utils/error.hpp"
#include "flite/utils/string.hpp"

size_t cst_regsub(const cst_regstate* state, const char* in, char* out, size_t max)
{
    const char* src;
    char* dst;
    int c, no, len;
    size_t count;

    if (state == NULL || in == NULL) {
        cst_errmsg("NULL parm to regsub\n");
        cst_error();
    }

    src = in;
    dst = out;
    count = 0;
    while ((c = *src++) != '\0') {
        if (out && dst + 1 > out + max - 1)
            break;
        if (c == '&')
            no = 0;
        else if (c == '\\' && '0' <= *src && *src <= '9')
            no = *src++ - '0';
        else
            no = -1;

        if (no < 0) { /* Ordinary character. */
            if (c == '\\' && (*src == '\\' || *src == '&'))
                c = *src++;
            if (out)
                *dst++ = c;
            count++;
        }
        else if (state->startp[no] != NULL && state->endp[no] != NULL) {
            len = state->endp[no] - state->startp[no];
            if (out) {
                if (dst + len > out + max - 1)
                    len = (out + max - 1) - dst;
                strncpy(dst, state->startp[no], len);
                dst += len;
                /* strncpy hit NUL. */
                if (len != 0 && *(dst - 1) == '\0') {
                    cst_errmsg("damaged match string");
                    cst_error();
                }
            }
            count += len;
        }
    }
    if (out && dst - out + 1 < (int)max)
        *dst++ = '\0';

    return count;
}
