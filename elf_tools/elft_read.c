/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elft_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:57:22 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/23 00:44:17 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elft.h"

// passing address of pointer (not an array)
inline int	elft_read_header(t_elf* elft)
{
	if (elft <= (t_elf*)0)
		return (-1);
	elft->header = (t_elf_header*)(elft_get_raw(elft)->data);
	elft->bits = elft->header->identification_field.bits_archi;
	return (0);
}

// stock all program headers
int	elft_read_program_headers(t_elf* elft)
{
	if (elft <= (t_elf*)0)
		return (-1);
	t_elf_raw*	raw = elft_get_raw(elft);
	elft->pHeaders = malloc(elft->header->program_headers_count * sizeof(t_elf_program_header));
	for (int i = 0 ; i < elft->header->program_headers_count ; ++i)
		elft->pHeaders[i] = (t_elf_program_header*)(raw->data + elft->header->program_headers_offset + i * sizeof(t_elf_program_header));
	return (0);
}

// stock all section headers
int	elft_read_section_headers(t_elf* elft)
{
	if (elft <= (t_elf*)0)
		return (-1);
	t_elf_raw*	raw = elft_get_raw(elft);
	elft->sHeaders = malloc(elft->header->section_headers_count * sizeof(t_elf_section_header));
	for (int i = 0 ; i < elft->header->section_headers_count ; ++i)
		elft->sHeaders[i] = (t_elf_section_header*)(raw->data + elft->header->section_headers_offset + i * sizeof(t_elf_section_header));
	return (0);
}

// only return a program header (must be read before)
t_elf_program_header*	elft_inspect_program_header(t_elf* elft, int section_id)
{
	(void)elft;
	(void)section_id;
	return (NULL);
}

// only return a section header (must be read before)
t_elf_section_header*	elft_inspect_section_header(t_elf* elft, unsigned int section_id, t_elf_section_header* current)
{
	for (int i = 0 ; i < elft->header->section_headers_count ; ++i)
		if (elft->sHeaders[i]->type == section_id && (!current || elft->sHeaders[i] > current))
			return (elft->sHeaders[i]);
	return (NULL);
}
