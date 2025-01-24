/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elft.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:05:37 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/23 00:50:09 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELFT_H
#define ELFT_H

# define ELFTSH_PROGRAM_DATA	SHT_PROGBITS
# define ELFTSH_SYMBOL			SHT_SYMTAB
# define ELFTSH_STRING			SHT_STRTAB
# define ELFTSH_RELA			SHT_RELA
# define ELFTSH_SYMBOL_HASH		SHT_HASH
# define ELFTSH_DYN_INFO		SHT_DYNAMIC
# define ELFTSH_NOTES			SHT_NOTE
# define ELFTSH_BSS				SHT_NOBITS
# define ELFTSH_REL				SHT_REL
# define ELFTSH_RESERVED		SHT_SHLIB
# define ELFTSH_DYNSYM			SHT_DYNSYM
# define ELFTSH_INIT_ARRAY		SHT_INIT_ARRAY
# define ELFTSH_END_ARRAY		SHT_FINI_ARRAY
# define ELFTSH_PREINIT_ARRAY	SHT_PREINIT_ARRAY
# define ELFTSH_GROUP			SHT_GROUP
# define ELFTSH_SYM_EXT			SHT_SYMTAB_SHNDX

# define ELFT_SUCCESS				0
# define ELFT_INVALID_FD			1
# define ELFT_MALLOC_FAILED			2
# define ELFT_MMAP_FAILED			3
# define ELFT_INVALID_FILE_FORMAT	4

# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <elf.h>
# include "libft.h"

typedef char		elftByte;
typedef short		elftWord;
typedef int			elftDouble;
typedef long long	elftQuad;


typedef unsigned char		elftByteU;
typedef unsigned short		elftWordU;
typedef unsigned int		elftDoubleU;
typedef unsigned long long	elftQuadU;

typedef struct s_elf_identification
{
	elftByteU	magic_numbers[4];
	elftByteU	bits_archi;
	elftByteU	endianness;
	elftByteU	header_format_version;
	elftByteU	ABI;
	elftByteU	ABI_version;
	elftByteU	__tamping__[6];
	elftByteU	identification_field_size;
}	t_elf_identification;

// Header struct for ELF 64bits binary file
typedef struct s_elf_header
{
	t_elf_identification	identification_field;
	elftWordU				file_type;
	elftWordU				proc_target;
	elftDouble				version;
	elftQuad				entry_point;
	elftQuadU				program_headers_offset;
	elftQuadU				section_headers_offset;
	elftDoubleU				proc_flags;
	elftWordU				header_size;
	elftWordU				program_headers_size;	// Size of an entry in the section header table (in bytes)
	elftWordU				program_headers_count;	// Number of entries in the section header table
	elftWordU				section_headers_size;	// Size of an entry in the table containing the programme header (in bytes)
	elftWordU				section_headers_count;	// Number of entries in the table containing the programme header
	elftWordU				sections_names_offset;	// Index in the table of section headings of the entry associated with the table containing the names of the sections
}	t_elf_header;

# if defined(__x86_64__) || defined(__ppc64__) || defined(__arm64__)
typedef struct s_elf_program_header
{
	elftDouble	segment_type; //Identifies the type of the segment. 
	elftDouble	segment_dep_flags;	// only 64bits architecture
	elftQuad	segment_offset;	// Offset of the segment in the file image. 
	elftQuad	VAddress_of_segment;	// Virtual address of the segment in memory. 
	elftQuad	PAddress_of_segment;	// On systems where physical address is relevant, reserved for segment's physical address.
	elftQuad	segment_size;	// Size in bytes of the segment in the file image. May be 0.
	elftQuad	segment_mem_size; // Size in bytes of the segment in memory. May be 0.
	elftQuad	segment_alignement;  // 0 and 1 specify no alignment. Otherwise should be a positive, integral power of 2, with p_vaddr equating p_offset modulus p_align.
	//elftByteU	__end_tamping__[8];
}	t_elf_program_header;
# else
typedef struct s_elf_program_header
{
	elftDouble	segment_type; //Identifies the type of the segment. 
	elftQuad	segment_offset;	// Offset of the segment in the file image. 
	elftQuad	VAddress_of_segment;	// Virtual address of the segment in memory. 
	elftQuad	PAddress_of_segment;	// On systems where physical address is relevant, reserved for segment's physical address.
	elftQuad	segment_size;	// Size in bytes of the segment in the file image. May be 0.
	elftQuad	segment_mem_size; // Size in bytes of the segment in memory. May be 0.
	elftDouble	segment_dep_flags;	// only 32bits architecture
	elftQuad	segment_alignement;  // 0 and 1 specify no alignment. Otherwise should be a positive, integral power of 2, with p_vaddr equating p_offset modulus p_align.
	//elftByteU	__end_tamping__[4];
}	t_elf_program_header;
# endif

typedef struct s_elf_section_header
{
	elftDoubleU	name_offset;
	elftDoubleU	type;
	elftQuadU	flags;
	elftQuadU	VAddress_of_section;
	elftQuadU	offset;
	elftQuadU	size;
	elftDoubleU	link;	// Contains the section index of an associated section. This field is used for several purposes, depending on the type of section. 
	elftDoubleU	info;	// Contains extra information about the section. This field is used for several purposes, depending on the type of section.
	elftQuadU	required_alignement; // Contains the required alignment of the section. This field must be a power of two. 
	elftQuadU	entry_size;	// Contains the size, in bytes, of each entry, for sections that contain fixed-size entries. Otherwise, this field contains zero.
	//elftByteU	__end_tamping__[8];
}	t_elf_section_header;

typedef struct s_elf
{
	int						bits;
	t_elf_header*			header;
	t_elf_program_header**	pHeaders;
	t_elf_section_header**	sHeaders;
	void*	__p;
}	t_elf;

typedef struct	s_elf_raw
{
	int		fd;
	int		data_size;
	char*	data;
}	t_elf_raw;

# if defined(__x86_64__) || defined(__ppc64__) || defined(__arm64__)
typedef struct	s_elf_symbol
{
	elftDoubleU	name_offset;
	elftByteU	info;
	elftByteU	other;
	elftWordU	index;
	elftQuadU	value;
	elftQuadU	size;
}	t_elf_symbol;
# else
typedef struct	s_elf_symbol
{
	elftDoubleU	name_offset;
	elftQuadU	value;
	elftQuadU	size;
	elftByteU	info;
	elftByteU	other;
	elftWordU	index;
}	t_elf_symbol;
# endif

const char*				whichEndianness(elftByteU header_value);
int						ELFbits(elftByteU header_value);
int						isELF(elftByteU header_magic_number[4]);
const char*				whichTypeFile(elftWordU header_value);
const char*				whichProcTarget(elftWordU header_value);
const char* 			kindSegmentType(elftDoubleU val);
const char*				kindSectionType(elftDoubleU val);

t_elf*					elft_init(int fd, int prot_flags, int* __restrict__ nullable_errorcode);
int						elft_destroy(t_elf* elft);
t_elf_raw*				elft_get_raw(t_elf* elft);

void	elft_debug_header(t_elf_header* header);
void	elft_debug_program_headers(t_elf* elft, int count);
void	elft_debug_section_headers(t_elf* headers, int count);

t_elf_symbol*	elft_jump_to_symbol(char* data, t_elf_section_header* h);
char*			elft_get_strtab_section(t_elf* elft, int* strtab_size);

int					elft_read_header(t_elf* elft);
int					elft_read_program_headers(t_elf* elft);
int					elft_read_section_headers(t_elf* elft);
t_elf_program_header*	elft_inspect_program_header(t_elf* elft, int section_id);
t_elf_section_header*	elft_inspect_section_header(t_elf* elft, unsigned int section_id, t_elf_section_header* current);

#endif
