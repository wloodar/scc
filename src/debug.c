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
#include <svm/debug.h>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>


void debug_pwin(const char *file, const char *func, const char *fmt, ...)
{
#ifdef DEBUG
    va_list args;
    va_start(args, fmt);

    printf("%s::%s \t ", file, func);
    vprintf(fmt, args);

    va_end(args);
#endif
}

void debug_plinux(const char *file, const char *func, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    u32 pos = 0;
    for (u32 i = 0; i < strlen(file); i++) {
        if (file[i] == '/')
            pos = i + 1;
    }

    i32 file_size = (i32) strlen(file);
    i32 func_size = (i32) strlen(func);

    char path[file_size + func_size];
    memset(path, 0, file_size + func_size);
    strncpy(path, file + pos, file_size - 2 - pos);

    const char *fmt_str = "\033[96m%*s\033[0m \033[90m: \033[92m%s%*c\033[90m|\033[0m ";
    printf(fmt_str, 14, path, func, 24 - func_size, ' ');

    vprintf(fmt, args);
    printf("\n");

    va_end(args);
}
