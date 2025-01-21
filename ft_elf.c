/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:07:09 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/21 18:32:39 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_elf.h"
#include "libft.h"

int	isELF(nmByte8U header_magic_number[4])
{
	if (header_magic_number[0] == 0x7f && !ft_strncmp((char*)&header_magic_number[1], "ELF", 3))
		return (1);
	return (0);
}

int	ELFbits(nmByte8U val)
{
	if (val == ELFCLASSNONE)
		return (0);
	else if (val == ELFCLASS32)
		return (32);
	else if (val == ELFCLASS64)
		return (64);
	return (0);
}

const char*	whichEndianness(nmByte8U val)
{
	if (val == ELFDATANONE)
		return ("None");
	else if (val == ELFDATA2LSB)
		return ("Little (LSB)");
	else if (val == ELFDATA2MSB)
		return ("Big (MSB)");
	return ("Unknow");
}

const char*	whichProcTarget(nmWord16U val)
{
	switch (val)
	{
		case EM_NONE:
			return ("None");
		case EM_M32:
			return ("AT&T WE 32100");
		case EM_SPARC:
			return ("Sun Microsystems SPARC");
		case EM_386:
			return ("Intel 80386");
		case EM_68K:
			return ("Motorola 68000");
		case EM_88K:
			return ("Motorola 88000");
		case EM_860:
			return ("Intel i860 (80860)");
		case EM_MIPS:
			return ("MIPS RS3000 (big-endian only)");
		case EM_PARISC:
			return ("HP/PA");
		case EM_SPARC32PLUS:
			return ("SPARC with enhanced instruction set");
		case EM_960:
			return ("Intel i960");
		case EM_PPC:
			return ("PowerPC");
		case EM_PPC64:
			return ("PowerPC 64-bit");
		case EM_S390:
			return ("IBM S/390");
		case EM_ARM:
			return ("ARM");
		case EM_SH:
			return ("Renesas SuperH");
		case EM_SPARCV9:
			return ("SPARC v9 64-bit");
		case EM_IA_64:
			return ("Intel Itanium (IA64)");
		case EM_X86_64:
			return ("AMD x86-64");
		case EM_VAX:
			return ("DEC Vax");
		case EM_RISCV:
			return ("RISC-V");
		default:
			return ("Unknow");
	}
}

const char*	whichTypeFile(nmWord16U val)
{
	if (val == ET_NONE)
		return ("None");
	else if (val == ET_REL)
		return ("Relocatable");
	else if (val == ET_EXEC)
		return ("Executable");
	else if (val == ET_DYN)
		return ("Shared object (DYN)");
	else if (val == ET_CORE)
		return ("Core file");
	return ("Unknow");
}

const char* kindSegmentType(nmDouble32U val)
{
	switch (val)
	{
		case PT_NULL:
			return ("Program header table entry unused.");
		case PT_LOAD:
			return ("Loadable segment.");
		case PT_DYNAMIC:
			return ("Dynamic linking information.");
		case PT_INTERP:
			return ("Interpret information.");
		case PT_NOTE:
			return ("Auxiliary information.");
		case PT_SHLIB:
			return ("Reserved.");
		case PT_PHDR:
			return ("Segment containing program header itself.");
		case PT_TLS:
			return ("Thread-Local Storage template.");
		case PT_LOOS:
		case PT_HIOS:
			return ("Reserved inclusive range. Operating system specific.");
		case PT_LOPROC:
		case PT_HIPROC:
			return ("Reserved inclusive range. Processor specific.");
		default:
			return ("Unknow");
	}
}

const char*	kindSectionType(nmDouble32U val)
{
	switch (val)
	{
		case SHT_NULL:
			return ("Section header table entry unused.");
		case SHT_PROGBITS:
			return ("Programme data");
		case SHT_SYMTAB:
			return ("Symbol table");
		case SHT_STRTAB:
			return ("String table");
		case SHT_RELA:
			return ("Relocation entries with addends");
		case SHT_HASH:
			return ("Symbol hash table");
		case SHT_DYNAMIC:
			return ("Dynamic linking information");
		case SHT_NOTE:
			return ("Notes");
		case SHT_NOBITS:
			return ("Program space with no data (bss)");
		case SHT_REL:
			return ("Relocation entries, no addends");
		case SHT_SHLIB:
			return ("Reserved");
		case SHT_DYNSYM:
			return ("Dynamic linker symbol table");
		case SHT_INIT_ARRAY:
			return ("Array of constructors");
		case SHT_FINI_ARRAY:
			return ("Array of destructors");
		case SHT_PREINIT_ARRAY:
			return ("Array of pre-constructors");
		case SHT_NUM:
			return ("Number of defined types");
		case SHT_LOOS:
			return ("Start OS-specific");
		default:
			return ("Unknow");
	}
}

// archi = 32/64
//Todo: an array of ULL (for each section address non-null found)
t_nm_generic_header*	findAddressOfSectionType(nmDouble32U sectionType, t_nm_generic_header** header, int count, int archi)
{
	for (int i = 0 ; i < count ; ++i)
	{ 
		if (archi == 64 && (((t_elf64_section_header**)header)[i])->type == sectionType)
			return ((((t_nm_generic_header**)header)[i]));
		else if (archi == 32 && (((t_elf32_section_header**)header)[i])->type == sectionType)
			return ((((t_nm_generic_header**)header)[i]));
	}
	return (0);
}
