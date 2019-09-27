#pragma once

#include <wchar.h>

wchar_t* cst_cstr2wstr(const char* s);
char* cst_wstr2cstr(const wchar_t* s);

#define cst_wstrlen(X) wcslen(X)
