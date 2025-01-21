/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:40:38 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/21 03:32:01 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

# define NM_INIT			-1
# define NM_DESTROY			1

# define NM_SUCCESS			0
# define NM_FAILED_MMAP		1
# define NM_FAILED_MUNMAP	2
# define NM_FAILED_OPEN		3
# define NM_FAILED_CLOSE	4
# define NM_FAILED_NO_ELF	5

# define NM_NO_ENDIAN_INFO	0
# define NM_LITTLE_ENDIAN	1
# define NM_MIDDLE_ENDIAN	2

# ifndef PAGESIZE
#  define PAGESIZE	_SC_PAGE_SIZE
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <elf.h>

typedef char	nmByte8;
typedef short	nmWord16;
typedef int		nmDouble32;
typedef long	nmQuad64;

typedef unsigned char	nmByte8U;
typedef unsigned short	nmWord16U;
typedef unsigned int	nmDouble32U;
typedef unsigned long	nmQuad64U;

typedef struct s_nm_options
{
	int	header;
	int	section_headers;
	int	program_headers;
}	t_nm_options;

typedef struct s_nm_generic_header
{
}	t_nm_generic_header;

typedef struct s_elf_identification
{
	nmByte8U	magic_numbers[4];
	nmByte8U	bits_archi;
	nmByte8U	endianness;
	nmByte8U	header_format_version;
	nmByte8U	ABI;
	nmByte8U	ABI_version;
	nmByte8U	__tamping__[6];
	nmByte8U	identification_field_size;
}	t_elf_identification;

// Header struct for ELF 64bits binary file
typedef struct s_elf64_header
{
	t_elf_identification	identification_field;
	nmWord16U				file_type;
	nmWord16U				proc_target;
	nmDouble32				version;
	nmQuad64				entry_point;
	nmQuad64U				header_table_offset;
	nmQuad64U				sections_table_offset;
	nmDouble32U				proc_flags;
	nmWord16U				header_size;
	nmWord16U				eiStsize;			// Size of an entry in the section header table (in bytes)
	nmWord16U				eNis;				// Number of entries in the section header table
	nmWord16U				eiHtPsize;			// Size of an entry in the table containing the programme header (in bytes)
	nmWord16U				eNiHtP;				// Number of entries in the table containing the programme header
	nmWord16U				IitsH_ascted_wtcSN;	// Index in the table of section headings of the entry associated with the table containing the names of the sections
}	t_elf64_header;

// Header struct for ELF 32bits binary file
typedef struct s_elf32_header
{
	t_elf_identification	identification_field;
	nmWord16U				file_type;
	nmWord16U				proc_target;
	nmDouble32				version;
	nmDouble32				entry_point;
	nmDouble32U				header_table_offset;
	nmDouble32U				sections_table_offset;
	nmDouble32U				proc_flags;
	nmWord16U				header_size;
	nmWord16U				eiStsize;			// Size of an entry in the section header table (in bytes)
	nmWord16U				eNis;				// Number of entries in the section header table
	nmWord16U				eiHtPsize;			// Size of an entry in the table containing the programme header (in bytes)
	nmWord16U				eNiHtP;				// Number of entries in the table containing the programme header
	nmWord16U				IitsH_ascted_wtcSN;	// Index in the table of section headings of the entry associated with the table containing the names of the sections
}	t_elf32_header;

// Header struct for COFF object file
typedef struct s_coff_header
{

}	t_coff_header;

typedef struct s_nm
{
	int				_err;
	int				fd;
	unsigned long	data_size;
	char*			data;
	struct
	{
		int				bits;
		union
		{
			t_elf64_header*	elf64;
			t_elf32_header*	elf32;
			t_coff_header*	coff;
		};
	}				bin_header;
}	t_nm;

void	ft_nm_options(int* ac_start_index, t_nm_options* options, int ac, char** av);

void	init_nm_struct(t_nm* nm_s, char* file);
void	destroy_nm_struct(t_nm *nm_s);
int		handle_errors(t_nm nm_s, int flag);
void	nm_print_header_info(const t_nm_generic_header* __restrict__ header, int size);

const char*	whichEndianness(nmByte8U header_value);
int			ELFbits(nmByte8U header_value);
int			isELF(nmByte8U header_magic_number[4]);
const char*	whichTypeFile(nmWord16U header_value);
const char*	whichProcTarget(nmWord16U header_value);

#endif
