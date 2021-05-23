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
#ifndef SCC_ARGPARSE_H
#define SCC_ARGPARSE_H

#include <svm/svmtypes.h>

/* This is the argument parser header which gives the argparse() function
   along with some structures and #defines for holding the argument parser
   result. */

/* SCC Toolkit options. */

#define OPT_ASSEMBLE        1
#define OPT_DISSASEMBLE     2
#define OPT_LINK            3
#define OPT_OPTIMIZE        4


typedef struct argresult_st {

    u8 option;      /* Option chosen by the user, like OPT_LINK */

} ArgumentResult;


/* Parses the arguments given in argc and argv, and fills the ArgumentResult
 * structure the main function will pass to it. This function will return 0
 * if everything goes well, but will close the application on it's own if
 * something goes wrong, along with a nice error message.
 *
 * @param   ar      the result struct
 * @param   argc    amount of arguments
 * @param   argv    arguments
 */
u32 argparse(ArgumentResult *ar, i32 argc, char **argv);


#endif /* SCC_ARGPARSE_H */
