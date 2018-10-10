//======================================================================================
// elf_arm.h
//======================================================================================
// $RCSfile: Gen6FoundationApp/FoundationApp/Plugin/elf_arm.h $
// $Revision: 3776 $
// $Date: 2012-09-26 23:15:21 +0800 (Wed, 26 Sep 2012) $
// $Author: Van, Volkinburg $
//======================================================================================

//======================================================================================


//---------------------------------------------------------------------------
//
//  Module Interface Description:
//    ARM architecture hardware depend type defines.
//
//---------------------------------------------------------------------------


#ifndef _MATRIX_ARM_TYPES_H
#define _MATRIX_ARM_TYPES_H

/*
 * __xx is ok: it doesn't pollute the POSIX namespace. Use these in the
 * header files exported to user space
 */

typedef signed char __s8;
typedef unsigned char __u8;

typedef signed short __s16;
typedef unsigned short __u16;

typedef signed int __s32;
typedef unsigned int __u32;

typedef signed long long __s64;
typedef unsigned long long __u64;

#define BITS_PER_LONG 32

#define ELF_CLASS ELFCLASS32		/* 32bit machine */
#define ELF_BIT_32

#define ElfSectionHeader		Elf32_Shdr
#define ElfSymbol			Elf32_Sym
#define ElfHeader			Elf32_Ehdr
#define ElfRelocation		Elf32_Rel
#define ElfSymbol			Elf32_Sym


/*
 * ELF register definitions..
 */

#define EM_ARM	40
#define EF_ARM_APCS26 0x08
#define EF_ARM_SOFT_FLOAT 0x200
#define EF_ARM_EABI_MASK 0xFF000000

#define R_ARM_NONE	0
#define R_ARM_PC24	1
#define R_ARM_ABS32	2
#define R_ARM_PLT32	27		/* Deprecated */
#define R_ARM_CALL	28
#define R_ARM_JUMP24	29
#define R_ARM_TARGET1	38
#define R_ARM_V4BX	40
#define R_ARM_MOVW_ABS_NC	43	/* Direct 16-bit (MOVW).  */
#define R_ARM_MOVT_ABS		44	/* Direct high 16-bit (MOVT).  */
#define R_ARM_REL32		3	/* PC relative 32 bit */

/* ARM sh_type */
#define SHT_ARM_EXIDX 0x70000001

/*
 * This is used to ensure we don't load something for the wrong architecture.
 */
#define ISArmArch(x) ( ((x)->e_machine == EM_ARM) && (ELF_PROC_OK((x))) )

/*
 * These are used to set parameters in the core dumps.
 */
#ifdef ARMEB
#define ELF_DATA	ELFDATA2MSB
#else
#define ELF_DATA	ELFDATA2LSB
#endif
#define ELF_ARCH	EM_ARM

#define USE_ELF_CORE_DUMP
#define ELF_EXEC_PAGESIZE	4096




/*
 * 32-bit code is always OK.  Some cpus can do 26-bit, some can't.
 */
#define ELF_PROC_OK(x) \
	((((x)->e_entry & 1) == 1) || \
	 ((x)->e_entry & 3) == 0)

#endif

//=================================================================================
//                       File Modification History
//===================================================================================
// $Log: Gen6FoundationApp/FoundationApp/Plugin/elf_arm.h  $
// Revision 1.2 2010/07/07 03:05:35EDT Huang,Will (E374983) 
// Added new logic of chaining plug-ins and system routines together
// Revision 1.1 2009/12/09 16:03:40GMT+08:00 Huang,Will (E374983) 
// Initial revision
// Member added to project d:/MKS_IT/Gen6FoundationApp/Gen6FoundationApp.pj
//===================================================================================


