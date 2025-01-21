/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:05:37 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/21 16:00:37 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ELF_H
#define FT_ELF_H

# include <elf.h>

typedef char	nmByte8;
typedef short	nmWord16;
typedef int		nmDouble32;
typedef long	nmQuad64;

typedef unsigned char	nmByte8U;
typedef unsigned short	nmWord16U;
typedef unsigned int	nmDouble32U;
typedef unsigned long	nmQuad64U;

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

typedef struct s_elf64_program_header
{
	nmDouble32	segment_type; //Identifies the type of the segment. 
	nmDouble32	segment_dep_flags;	// only 64bits architecture
	nmQuad64	segment_offset;	// Offset of the segment in the file image. 
	nmQuad64	VAddress_of_segment;	// Virtual address of the segment in memory. 
	nmQuad64	PAddress_of_segment;	// On systems where physical address is relevant, reserved for segment's physical address.
	nmQuad64	segment_size;	// Size in bytes of the segment in the file image. May be 0.
	nmQuad64	segment_mem_size; // Size in bytes of the segment in memory. May be 0.
	nmQuad64	segment_alignement;  // 0 and 1 specify no alignment. Otherwise should be a positive, integral power of 2, with p_vaddr equating p_offset modulus p_align.
	nmByte8U	__end_tamping__[8];
}	t_elf64_program_header;

typedef struct s_elf32_program_header
{
	nmDouble32	segment_type; //Identifies the type of the segment. 
	nmQuad64	segment_offset;	// Offset of the segment in the file image. 
	nmQuad64	VAddress_of_segment;	// Virtual address of the segment in memory. 
	nmQuad64	PAddress_of_segment;	// On systems where physical address is relevant, reserved for segment's physical address.
	nmQuad64	segment_size;	// Size in bytes of the segment in the file image. May be 0.
	nmQuad64	segment_mem_size; // Size in bytes of the segment in memory. May be 0.
	nmDouble32	segment_dep_flags;	// only 32bits architecture
	nmQuad64	segment_alignement;  // 0 and 1 specify no alignment. Otherwise should be a positive, integral power of 2, with p_vaddr equating p_offset modulus p_align.
	nmByte8U	__end_tamping__[4];
}	t_elf32_program_header;

typedef struct s_elf64_section_header
{
	nmByte8		name[4];
	nmDouble32U	type;
	nmQuad64U	flags;
	nmQuad64U	VAddress_of_section;
	nmQuad64U	offset;
	nmQuad64U	size;
	nmDouble32U	link;	// Contains the section index of an associated section. This field is used for several purposes, depending on the type of section. 
	nmDouble32U	info;	// Contains extra information about the section. This field is used for several purposes, depending on the type of section.
	nmQuad64U	required_alignement; // Contains the required alignment of the section. This field must be a power of two. 
	nmQuad64U	entry_size;	// Contains the size, in bytes, of each entry, for sections that contain fixed-size entries. Otherwise, this field contains zero.
	nmByte8U	__end_tamping__[8];
}	t_elf64_section_header;

typedef struct s_elf32_section_header
{
	nmByte8U	name[4];
	nmDouble32U	type;
	nmDouble32U	flags;
	nmDouble32U	VAddress_of_section;
	nmDouble32U	offset;
	nmDouble32U	size;
	nmDouble32U	link;	// Contains the section index of an associated section. This field is used for several purposes, depending on the type of section. 
	nmDouble32U	info;	// Contains extra information about the section. This field is used for several purposes, depending on the type of section.
	nmDouble32U	required_alignement; // Contains the required alignment of the section. This field must be a power of two. 
	nmDouble32U	entry_size;	// Contains the size, in bytes, of each entry, for sections that contain fixed-size entries. Otherwise, this field contains zero.
	nmByte8U	__end_tamping__[4];
}	t_elf32_section_header;

const char*	whichEndianness(nmByte8U header_value);
int			ELFbits(nmByte8U header_value);
int			isELF(nmByte8U header_magic_number[4]);
const char*	whichTypeFile(nmWord16U header_value);
const char*	whichProcTarget(nmWord16U header_value);
const char* kindSegmentType(nmDouble32U val);

#endif
