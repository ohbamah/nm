/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_header_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 01:08:55 by bama              #+#    #+#             */
/*   Updated: 2025/01/21 16:03:38 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "libft.h"

void	nm_print_header_info(const t_nm_generic_header* __restrict__ header, int flag)
{
	if (flag == NM_ELF_HEADER)
	{
		ft_printf("\t\e[1mEN-TÊTE:\e[0m\n");
		ft_printf("\tNombres magiques : 0x%x 0x%x 0x%x 0x%x\n", ((t_elf64_header*)header)->identification_field.magic_numbers[0], ((t_elf64_header*)header)->identification_field.magic_numbers[1], ((t_elf64_header*)header)->identification_field.magic_numbers[2], ((t_elf64_header*)header)->identification_field.magic_numbers[3]);
		ft_printf("\tELF%d\n", ELFbits(((t_elf64_header*)header)->identification_field.bits_archi));
		ft_printf("\tBoutisme (endianness) : %s\n", whichEndianness(((t_elf64_header*)header)->identification_field.endianness));
		ft_printf("\tHeader format version : %d\n", ((t_elf64_header*)header)->identification_field.header_format_version);
		ft_printf("\tABI : %d\n", ((t_elf64_header*)header)->identification_field.ABI);
		ft_printf("\tABI version : %d\n", ((t_elf64_header*)header)->identification_field.ABI_version);
		ft_printf("\tType de fichier : %s\n", whichTypeFile(((t_elf64_header*)header)->file_type));
		ft_printf("\tProcesseur (machine) cible : %s\n", whichProcTarget(((t_elf64_header*)header)->proc_target));
		ft_printf("\tVersion : %d\n", ((t_elf64_header*)header)->version);
		ft_printf("\tAddresse du point d'entrée : 0x%x\n", ((t_elf64_header*)header)->entry_point);
		printf("\tDébut des en-têtes de programme : %ld (octets)\n", ((t_elf64_header*)header)->header_table_offset);
		printf("\tDébut des en-têtes de section : %ld (octets)\n", ((t_elf64_header*)header)->sections_table_offset);
		ft_printf("\tNombre d'en-têtes de programme : %d\n", ((t_elf64_header*)header)->eNis);
		ft_printf("\tNombre d'en-têtes de section : %d\n", ((t_elf64_header*)header)->eNiHtP);
		ft_printf("\tTaille des en-têtes de programmes : %d (octets)\n", ((t_elf64_header*)header)->eiStsize);
		ft_printf("\tTaille des en-têtes de section : %d (octets)\n", ((t_elf64_header*)header)->eiHtPsize);
		ft_printf("\tTable d'index des chaînes d'en-têtes de section : %d\n", ((t_elf64_header*)header)->IitsH_ascted_wtcSN);
		ft_printf("\tProccessor flags : %d\n", ((t_elf64_header*)header)->proc_flags);
		ft_printf("\tHeader size : %d\n", ((t_elf64_header*)header)->header_size);
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (flag == NM_PROGRAM_HEADER)
	{
		ft_printf("\t\e[1mEN-TÊTES du PROGRAMME:\e[0m\n");
		ft_printf("\tType de segment : %s\n", kindSegmentType(((t_elf64_program_header*)header)->segment_type));
		ft_printf("\tSegment offset : %d\n", ((t_elf64_program_header*)header)->segment_offset);
		ft_printf("\tAdresse virtuelle d'emplacement du segment : %d\n", ((t_elf64_program_header*)header)->VAddress_of_segment);
		ft_printf("\tAdresse physique d'emplacement du segment : %d\n", ((t_elf64_program_header*)header)->PAddress_of_segment);
		ft_printf("\tFlag de dependance du segment : %d\n", ((t_elf64_program_header*)header)->segment_dep_flags);
		ft_printf("\tTaille du segment : %d\n", ((t_elf64_program_header*)header)->segment_size);
		ft_printf("\tAlignement memoire : %d\n", ((t_elf64_program_header*)header)->segment_alignement);
		ft_printf("\tTaille du segment en memoire : %d\n", ((t_elf64_program_header*)header)->segment_mem_size);
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (flag == NM_SECTION_HEADER)
	{
		ft_printf("\t\e[1mEN-TÊTES des SECTIONS:\e[0m\n");
		ft_printf("\tSection : %d\n", ((t_elf64_section_header*)header)->type);
	}
}
