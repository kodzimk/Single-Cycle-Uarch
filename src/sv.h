#ifndef SV_H_
#define SV_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    size_t count;
    const char *data;
} String_View;

#define SV_FORMAT(sv) (int) sv.count, sv.data

String_View sv_from_cstr(const char *cstr);
String_View sv_trim_left(String_View sv);
String_View sv_trim_right(String_View sv);
String_View sv_trim(String_View sv);
String_View sv_chop_by_delim(String_View *sv, char delim);
String_View sv_chop_by_index(String_View *sv, int start, int end);
bool sv_eq(String_View a, String_View b);

String_View sv_from_cstr(const char *cstr)
{
    String_View view;
    view.count = strlen(cstr);
    view.data = cstr;

    return view;
}

String_View sv_trim_left(String_View sv)
{
    size_t i = 0;
    while (i < sv.count && isspace(sv.data[i])) {
        i += 1;
    }

    String_View view;
    view.count = sv.count - i;
    view.data = sv.data + i;

    return view;
}


String_View sv_trim_right(String_View sv)
{
    size_t i = 0;
    while (i < sv.count && isspace(sv.data[sv.count - 1 - i])) {
        i += 1;
    }

    String_View view;
    view.count = sv.count - i;
    view.data = sv.data;

    return view;
}

String_View sv_trim(String_View sv)
{
    return sv_trim_right(sv_trim_left(sv));
}

String_View sv_chop_by_delim(String_View *sv, char delim)
{
    size_t i = 0;
    while (i < sv->count && sv->data[i] != delim) {
        i += 1;
    }

    String_View result;
    result.count = i;
    result.data = sv->data;

    if (i < sv->count) {
        sv->count -= i + 1;
        sv->data  += i + 1;
    } else {
        sv->count -= i;
        sv->data  += i;
    }

    return result;
}

String_View sv_chop_by_index(String_View *sv, int start, int end)
{
    size_t i = start;
    while (i < sv->count && i != end) {
        i += 1;
    }

    String_View result;
    result.count = i;
    result.data = sv->data;

    if (i < sv->count) {
        sv->count -= i + 1;
        sv->data  += i + 1;
    } else {
        sv->count -= i;
        sv->data  += i;
    }

    return result;
}

bool sv_eq(String_View a, String_View b)
{
    if (a.count != b.count) {
        return false;
    } else {
        return memcmp(a.data, b.data, a.count) == 0;
    }
}

#endif // STRING VIEW IMPLEMENTATION