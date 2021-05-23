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
#include <svm/runtime.h>
#include <svm/safety.h>
#include <svm/debug.h>
#include <svm/mmgr.h>

#include <stdio.h>
#include <stdlib.h>


static const char *FAIL_MSG = "svm: safety assertion failed in '%s' on "
                              "line %d\n  -> ";

static void vmexit()
{
#ifdef __saltvm__
    mmgr_close();
#endif

    exit(1);
}

void _assert_nn_strp(String *str, const char *func, i32 line)
{
    if (!str)
        goto fail;

    if (str->len && str->val)
        return;

fail:
    fprintf(stderr, FAIL_MSG, func, line);
    fprintf(stderr, "passed null string\n");
    vmexit();
}

void _assert_nn_str(String str, const char *func, i32 line)
{
    if (str.len && str.val)
        return;

    fprintf(stderr, FAIL_MSG, func, line);
    fprintf(stderr, "passed null string\n");
    vmexit();
}

void _assert_nn_ptr(void *ptr, const char *func, i32 line)
{
    if (ptr)
        return;

    fprintf(stderr, FAIL_MSG, func, line);
    fprintf(stderr, "passed null pointer\n");
    vmexit();
}

void _assert_not_implemented(const char *func)
{
    fprintf(stderr, "svm: assertion reached\n  -> '%s' is not implemented "
            "yet\n", func);
    vmexit();
}

void vmfail(char *msg)
{
    dprintf("Forcing an immediate exit");
    fprintf(stderr, "svm: %s\n", msg);
    vmexit();
}
