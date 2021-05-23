/**
 * SCC Toolkit
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
#include <scc/argparse.h>
#include <svm/debug.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef SCC_VERSION
# define SCC_VERSION "undefined"
#endif

#define ARG(SHORT, LONG) (!strcmp(argv[i], SHORT) || !strcmp(argv[i], LONG))


static void usage()
{
    printf(
        "Usage: scc [OPTION]... FILE\n"
        "scc - Salt Compiled Code Toolkit for assembling, disassembling, "
        "linking and optimizing SCC bytecode.\n\n"
        "  FILE                 file(s) to read from\n"
        "  -a, --assemble       assemble the Salt Assembly file\n"
        "  -d, --disassemble    disassemble compiled bytecode\n"
        "  -l, --link           link multiple SCC bytecode files\n"
        "  -h, --help           show this page and exit\n"
        "  -o, --output         specify the output file, default is stdout\n"
        "  -v, --version        show the current version\n"
    );

    exit(0);
}

static void version()
{
    printf("Salt Compiled Code Toolkit %s\n", SCC_VERSION);
    exit(0);
}

u32 argparse(ArgumentResult *ar, i32 argc, char **argv)
{
    dprintf("Parsing %d arguments", argc);

    for (i32 i = 0; i < argc; i++) {

        if (ARG("-h", "--help")) {
            usage();
        }
        else if (ARG("-v", "--version")) {
            version();
        }

    }
    return 0;
}
