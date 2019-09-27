#pragma once

#define CST_WRONG_FORMAT -2
#define CST_ERROR_FORMAT -1
#define CST_OK_FORMAT 0

#ifdef UNDER_CE
/* File access stuff (WinCE 2.11 is really damaged) */
#include <winbase.h>
#include <windows.h>
typedef HANDLE cst_file;
#elif __palmos__
#include <PalmOS.h>
#include <System/StdIOPalm.h>
typedef FILE* cst_file;
#else
#include <stdio.h>
typedef FILE* cst_file;
#endif

/* File mapping stuff */
#ifdef _WIN32
#include <windows.h>
typedef struct cst_filemap_struct {
    void* mem;
    cst_file fh;
    size_t mapsize;
    HANDLE h;
} cst_filemap;
#elif __palmos__
typedef struct cst_filemap_struct {
    void* mem;
    cst_file fh;
    unsigned int mapsize;
    int fd;
} cst_filemap;
#else
typedef struct cst_filemap_struct {
    void* mem;
    cst_file fh;
    size_t mapsize;
    int fd;
} cst_filemap;
#endif

#define CST_OPEN_WRITE (1 << 0)
#define CST_OPEN_READ (1 << 1)
#define CST_OPEN_APPEND (1 << 2)
/* We actually ignore this -- files are always opened in in binary mode */
#define CST_OPEN_BINARY (1 << 3)

#define CST_SEEK_ABSOLUTE 0
#define CST_SEEK_RELATIVE 1
#define CST_SEEK_ENDREL 2

cst_file cst_fopen(const char* path, int mode);
long cst_fwrite(cst_file fh, const void* buf, long size, long count);
long cst_fread(cst_file fh, void* buf, long size, long count);
int cst_fprintf(cst_file fh, const char* fmt, ...);
int cst_sprintf(char* s, const char* fmt, ...);
#ifdef _WIN32
#define snprintf c99_snprintf

__inline int c99_vsnprintf(char* str, size_t size, const char* format, va_list ap)
{
    int count = -1;
    if (size != 0)
        count = _vsnprintf_s(str, size, _TRUNCATE, format, ap);
    if (count == -1)
        count = _vscprintf(format, ap);
    return count;
}
__inline int c99_snprintf(char* str, size_t size, const char* format, ...)
{
    int count;
    va_list ap;

    va_start(ap, format);
    count = c99_vsnprintf(str, size, format, ap);
    va_end(ap);
    return count;
}
#endif
#define cst_snprintf snprintf

#if defined(__palmos__)
#include <stdarg.h>
int cst_vsprintf(char* s, const char* fmt, va_list args);
#endif
int cst_fclose(cst_file fh);
int cst_fgetc(cst_file fh);

/* These aren't LFS-compliant.  I don't think we'll need >2G files. */
long cst_ftell(cst_file fh);
long cst_fseek(cst_file fh, long pos, int whence);
long cst_filesize(cst_file fh);

cst_filemap* cst_mmap_file(const char* path);
int cst_munmap_file(cst_filemap* map);

cst_filemap* cst_read_whole_file(const char* path);
int cst_free_whole_file(cst_filemap* map);

cst_filemap* cst_read_part_file(const char* path);
int cst_free_part_file(cst_filemap* map);

int cst_urlp(const char* url);
cst_file cst_url_open(const char* url);
