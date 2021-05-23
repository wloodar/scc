/**
 * Salt Virtual Machine
 *
 * Copyright (C) 2021  The Salt Programming Language Developers
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * END OF COPYRIGHT NOTICE
 *
 * @author  bellrise
 */
#include <svm/svmtypes.h>
#include <svm/string.h>
#include <svm/safety.h>
#include <svm/debug.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef STR_DEBUG
#define sdprintf(...) dprintf(__VA_ARGS__)
#else
#define sdprintf(...)
#endif


String *str_make(char *src)
{
    String *str = malloc(sizeof(String));
    str->len = 0;
    str->val = NULL;

    u64 src_len = strlen(src);
    str->val = malloc(sizeof(char) * (src_len + 1));
    str->len = src_len;

    strncpy(str->val, src, src_len);
    str->val[src_len] = 0;

    sdprintf("make len=%lu", str->len);

    return str;
}

String *str_read(char *src, u64 len)
{
    String *str = malloc(sizeof(String));
    str->len = len;
    str->val = malloc(sizeof(char) * (len + 1));

    strncpy(str->val, src, len);
    str->val[len] = 0;

    sdprintf("read len=%lu", str->len);

    return str;
}

void str_del(String *str)
{
    if (!str)
        return;

    sdprintf("del len=%lu", str->len);

    free(str->val);
    free(str);
}

String *str_copy(String *src)
{
    assert_nonnull(src);

    String *new_str = str_make(src->val);
    return new_str;
}

u8 str_eq(String *str1, String *str2)
{
    assert_nonnull(str1);
    assert_nonnull(str2);

    if (str1->len != str2->len)
        return False;

    if (strncmp(str1->val, str2->val, str1->len) == 0)
        return True;
    return False;
}

u8 str_startswith(String *str, char *start)
{
    assert_nonnull(str);

    if (strlen(start) > str->len)
        return False;

    if (strncmp(str->val, start, strlen(start)) == 0)
        return True;
    return False;
}

u8 str_endswith(String *str, char *end)
{
    assert_nonnull(str);

    u64 endl = strlen(end);
    if (endl > str->len)
        return False;

    char *view = str->val + (str->len - endl);

    if (strncmp(view, end, endl) == 0)
        return True;
    return False;
}

String *str_segment(String *str, u64 from, u64 to)
{
    assert_nonnull(str);

    if (from >= str->len || from >= to)
        return str;

    if (to > str->len)
        to = str->len;

    sdprintf("from=%lu to=%lu", from, to);

    str->val[to] = '\0';
    String *new_str = str_make(str->val + from);
    str_del(str);
    return new_str;
}

String *str_segment_left(String *str, char sep)
{
    assert_nonnull(str);

    u64 seperator_pos = str->len;
    for (u64 i = 0; i < str->len; i++) {
        if (str->val[i] == sep) {
            seperator_pos = i;
            break;
        }
    }

    if (seperator_pos == str->len)
        return str;

    str->val[seperator_pos] = '\0';
    String *new_str = str_make(str->val);

    str_del(str);
    return new_str;
}

String *str_segment_right(String *str, char sep)
{
    assert_nonnull(str);

    u64 seperator_pos = str->len;
    for (u64 i = 0; i < str->len; i++) {
        if (str->val[i] == sep)
            seperator_pos = i;
    }

    if (seperator_pos == str->len)
        return str;

    String *new_str = str_make(str->val + seperator_pos + 1);
    str_del(str);
    return new_str;
}

String *str_cat(String *str, char *src)
{
    u64 strl = strlen(src);
    str->val = realloc(str->val, str->len + 1 + strl);

    memcpy(str->val + str->len, src, strl);
    str->len += strl;
    str->val[str->len] = 0;
    return str;
}
