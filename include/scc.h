/**
 * Standalone header
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
 */
#ifndef SCC_H
#define SCC_H

/* README
 *
 * Because this a standalone header, it does not require any SVM headers and it
 * is not developed in any relation with the current SVM version. This is
 * designed so it can be included in both C++ and C code, providing different
 * ways of accessing the values, without a difference in implementations. Also,
 * this header does not have any header dependency (only a sane compiler).
 *
 * GUARANTEE: NO SYMBOL WILL BE CHANGED OR REMOVED FROM THIS HEADER, IT CAN
 * ONLY BECOME DEPRECATED.
 */

/* UTILITY TYPEDEFS */

typedef __INT8_TYPE__   _scc_i8_t;
typedef __INT32_TYPE__  _scc_i32_t;
typedef __INT64_TYPE__  _scc_i64_t;
typedef __UINT8_TYPE__  _scc_u8_t;
typedef __UINT32_TYPE__ _scc_u32_t;
typedef __UINT64_TYPE__ _scc_u64_t;


#define SCC3_MAGIC (*(_scc_u64_t*) "\x7fSCC\xff\xee\0\0")
#define SCC3_VERSION ((_scc_u64_t) 3)

#define SCC4_MAGIC (*(_scc_u64_t*) "\x7fSCC4\xee\0\0")
#define SCC4_VERSION ((_scc_u64_t) 4)


/* STRUCTURES */

/* All SCC headers must have one thing in common: the first 16 bytes are the
   magic number and the SCC format version number. This allows for easy
   identification of SCC formats. Each header struct is defined as packed,
   so we are sure the compiler does not expand the header. */


struct __attribute__((__packed__)) SCC3_Header /* 64 bytes */
{
    _scc_u64_t  h_magic;            /* Magic number */
    _scc_u64_t  h_version;          /* SCC format version */
    _scc_u32_t  m_ins;              /* Instruction amount */
    _scc_u8_t   pad1[4];
    _scc_u8_t   m_reg;              /* Register amount */
    _scc_u8_t   pad2[7];
    _scc_u8_t   pad3[24];
    _scc_u32_t  s_pre;              /* Signature prefix */
    _scc_u32_t  s_comp;             /* Compiler signature */
};


struct __attribute__((__packed__)) SCC4_Header /* 64 bytes */
{
    _scc_u64_t  h_magic;            /* Magic number */
    _scc_u64_t  h_version;          /* SCC format version */
    _scc_u32_t  m_ins;              /* Amount of instructions */
    _scc_u8_t   m_reg;              /* Amount of registers */
    _scc_u8_t   f_load;             /* Use private load function */
    _scc_u8_t   f_unload;           /* Use private unload function */
    _scc_u8_t   f_standalone;       /* Standalone module flag */
    _scc_i32_t  c_timestamp;        /* Compilation time */
    _scc_u64_t  c_signature;        /* Compiler signature */
    _scc_u8_t   c_sys;              /* System the SCC was compiled on */
    _scc_u32_t  m_symbols;          /* Amount of symbols in the module */
    _scc_u8_t   r_use;              /* True if the runtime lib should be used */
    _scc_u8_t   r_lib[22];          /* Name of the runtime lib to find */
};


/* SCC4 MARKERS */

#define SCC4_TRUE           0x01
#define SCC4_FALSE          0x00
#define SCC4_MPUBLIC        '@'     /* Public marker */
#define SCC4_MPRIVATE       '%'     /* Private marker */
#define SCC4_MINSTRUCTION   '&'     /* Instruction marker */

/* SYSTEMS */

#define SCC4_SYSUNDEF       0x00
#define SCC4_SYSLINUX       0x01
#define SCC4_SYSWIN         0x02
#define SCC4_SYSSERENITY    0x03

/* BASE TYPES */

#define SCC4_NULL           0x00
#define SCC4_INT            0x01
#define SCC4_FLOAT          0x02
#define SCC4_BOOL           0x03
#define SCC4_STRING         0x04
#define SCC4_ARRAY          0x05

/* SCC4 INSTRUCTIONS */

#define SCC4_NOP            0x00    /* No operation */
#define SCC4_EXIT           0x01    /* Exit execution */
#define SCC4_LOAD           0x02    /* Load module */
#define SCC4_UNLOAD         0x03    /* Unload module */
#define SCC4_RETURN         0x04    /* Return from function */
#define SCC4_CALL           0x05    /* Call function */
#define SCC4_CALLEXT        0x06    /* Call external function */
#define SCC4_DUMPOBJ        0x07    /* Dump object */
#define SCC4_DUMPSTATE      0x08    /* Dump the svm state */
#define SCC4_DUMPMEM        0x09    /* Dump the object heap */
#define SCC4_NEW            0x0a    /* Create an object */
#define SCC4_DELETE         0x0b    /* Delete an object */
#define SCC4_RMOVE          0x0c    /* Move an object into a register */
#define SCC4_RCOPY          0x0d    /* Copy an object into a register */
#define SCC4_RGET           0x0e    /* Fetch an object from a register */


#endif /* SCC_H */
