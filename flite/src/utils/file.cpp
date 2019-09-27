#include "flite/utils/file.hpp"
#include "flite/utils/alloc.hpp"
#include "flite/utils/error.hpp"
#include "flite/utils/string.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

cst_file cst_fopen(const char* path, int mode)
{
    char cmode[4];

    if (cst_urlp(path))
        return cst_url_open(path);
    else if ((mode & CST_OPEN_WRITE) && (mode & CST_OPEN_READ))
        strcpy(cmode, "r+");
    else if ((mode & CST_OPEN_APPEND) && (mode & CST_OPEN_READ))
        strcpy(cmode, "a+");
    else if (mode & CST_OPEN_WRITE)
        strcpy(cmode, "w");
    else if (mode & CST_OPEN_APPEND)
        strcpy(cmode, "a");
    else if (mode & CST_OPEN_READ)
        strcpy(cmode, "r");

    /* Windows likes to make a distinction between binary and not */
    /* While other operating systems do not -- we're going to always */
    /* treat files as binary, because the non-binary Windows case is */
    /* never what we want */
    strcat(cmode, "b");

    return fopen(path, cmode);
}

long cst_fwrite(cst_file fh, const void* buf, long size, long count)
{
    return fwrite(buf, size, count, fh);
}

long cst_fread(cst_file fh, void* buf, long size, long count)
{
    return fread(buf, size, count, fh);
}

long cst_filesize(cst_file fh)
{
    /* FIXME: guaranteed to break on text files on Win32 */
    long pos, epos;

    pos = ftell(fh);
    fseek(fh, 0, SEEK_END);
    epos = ftell(fh);
    fseek(fh, pos, SEEK_SET);

    return epos;
}

int cst_fgetc(cst_file fh)
{
    return fgetc(fh);
}

long cst_ftell(cst_file fh)
{
    return ftell(fh);
}

long cst_fseek(cst_file fh, long pos, int whence)
{
    int w = 0;

    if (whence == CST_SEEK_ABSOLUTE)
        w = SEEK_SET;
    else if (whence == CST_SEEK_RELATIVE)
        w = SEEK_CUR;
    else if (whence == CST_SEEK_ENDREL)
        w = SEEK_END;

    fseek(fh, pos, w);

    return ftell(fh);
}

int cst_fprintf(cst_file fh, const char* fmt, ...)
{
    va_list args;
    int rv;

    va_start(args, fmt);
    rv = vfprintf(fh, fmt, args);
    va_end(args);

    return rv;
}

int cst_sprintf(char* s, const char* fmt, ...)
{
    va_list args;
    int rv;

    va_start(args, fmt);
    rv = vsprintf(s, fmt, args);
    va_end(args);

    return rv;
}

int cst_fclose(cst_file fh)
{
    return fclose(fh);
}
