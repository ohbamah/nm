/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elft_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:34:23 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/22 18:18:51 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elft.h"

void	elft_debug_header(t_elf_header* header)
{
	ft_printf("\e[1mEN-TÊTE:\e[0m\n");
	ft_printf("Nombres magiques : 0x%x 0x%x 0x%x 0x%x\n", header->identification_field.magic_numbers[0], header->identification_field.magic_numbers[1], header->identification_field.magic_numbers[2], header->identification_field.magic_numbers[3]);
	ft_printf("ELF%d\n", ELFbits(header->identification_field.bits_archi));
	ft_printf("Boutisme (endianness) : %s\n", whichEndianness(header->identification_field.endianness));
	ft_printf("Header format version : %d\n", header->identification_field.header_format_version);
	ft_printf("ABI : %d\n", header->identification_field.ABI);
	ft_printf("ABI version : %d\n", header->identification_field.ABI_version);
	ft_printf("Type de fichier : %s\n", whichTypeFile(header->file_type));
	ft_printf("Processeur (machine) cible : %s\n", whichProcTarget(header->proc_target));
	ft_printf("Version : %d\n", header->version);
	ft_printf("Addresse du point d'entrée : 0x%x\n", header->entry_point);
	ft_printf("Début des en-têtes de programme : %d (octets)\n", header->program_headers_offset);
	ft_printf("Début des en-têtes de section : %d (octets)\n", header->section_headers_offset);
	ft_printf("Nombre d'en-têtes de programme : %d\n", header->program_headers_count);
	ft_printf("Nombre d'en-têtes de section : %d\n", header->section_headers_count);
	ft_printf("Taille des en-têtes de programmes : %d (octets)\n", header->program_headers_size);
	ft_printf("Taille des en-têtes de section : %d (octets)\n", header->section_headers_size);
	ft_printf("Table d'index des chaînes d'en-têtes de section : %d\n", header->IitsH_ascted_wtcSN);
	ft_printf("Proccessor flags : %d\n", header->proc_flags);
	ft_printf("Header size : %d\n", header->header_size);
	write(STDOUT_FILENO, "\n", 1);
}

void	elft_debug_program_headers(t_elf* elft, int count)
{
	(void)elft;
	(void)count;
}

void	elft_debug_section_headers(t_elf* elft, int count)
{
	t_elf_raw*				raw = elft_get_raw(elft);
	t_elf_section_header*	elf_strtab = elft_inspect_section_header(elft, ELFTSH_STRING, NULL);
	t_elf_section_header*	elftab = elft_inspect_section_header(elft, ELFTSH_DYNSYM, NULL);

	ft_printf("\e[1mEN-TÊTES de SECTION:\e[0m\n");
	for (int i = 0 ; elftab && i < elftab->size ; ++i)
	{
		if ((raw->data + elftab->offset)[i] == '\0')
			write(1, "\\0", 1);
		else
			write(1, &(raw->data + elftab->offset)[i], 1);
	}
	for (int i = 0 ; i < count ; ++i)
	{
		if (elft->sHeaders[i]->VAddress_of_section == 0)
			continue ;
		ft_printf("[%d]\t%p -->\t%s\n", i, elft->sHeaders[i]->VAddress_of_section, kindSectionType(elft->sHeaders[i]->type));
	}
	write(STDOUT_FILENO, "\n", 1);
}
