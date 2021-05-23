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
#ifndef SVM_SVMTYPES_H
#define SVM_SVMTYPES_H 1

/* This provides the base typedefs and base structs used in all of SVM. For
   building SVMLs, use this header to get all the nice integer types. */

typedef __INT8_TYPE__       i8;
typedef __INT16_TYPE__      i16;
typedef __INT32_TYPE__      i32;
typedef __INT64_TYPE__      i64;
typedef __UINT8_TYPE__      u8;
typedef __UINT16_TYPE__     u16;
typedef __UINT32_TYPE__     u32;
typedef __UINT64_TYPE__     u64;


#define True    (1)
#define False   (0)

#define BOOL_STRING(BOOL) ((BOOL) ? "True" : "False")


#endif /* SVM_SVMTYPES_H */
