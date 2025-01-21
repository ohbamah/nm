/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_header_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 01:08:55 by bama              #+#    #+#             */
/*   Updated: 2025/01/21 03:24:07 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
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
