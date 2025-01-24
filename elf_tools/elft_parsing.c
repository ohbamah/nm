/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elft_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:34:43 by bama              #+#    #+#             */
/*   Updated: 2025/01/23 00:23:59 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elft.h"

// strtab_size --> nullable
inline char*	elft_get_strtab_section(t_elf* elft, int* strtab_size)
{
	t_elf_raw*	raw = elft_get_raw(elft);
	t_elf_section_header* strtab_section = elft_inspect_section_header(elft, ELFTSH_STRING, NULL);
	if (!strtab_section)
		return (NULL);
	if (strtab_size)
		*strtab_size = strtab_section->size;
	return (raw->data + strtab_section->offset);
}

inline t_elf_symbol*	elft_jump_to_symbol(char* data, t_elf_section_header* header)
{
	return ((t_elf_symbol*)(data + header->offset));
}
