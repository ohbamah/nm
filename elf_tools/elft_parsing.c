/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elft_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:34:43 by bama              #+#    #+#             */
/*   Updated: 2025/01/27 17:57:53 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elft.h"

// local	-> lowercase
// global	-> uppercase (no 'u', 'v' and 'w')
char	elft_get_sym_type(t_elf* elft, t_elf_symbol* sym)
{
	//char	stt = sym->info & 0xF;	// type
	char	stb = sym->info >> 4;	// linking (binding)
	int		shn = sym->index;		// index

	if (shn == SHN_UNDEF)
		return ((stb == STB_WEAK) ? 'w' : 'U');
	t_elf_section_header* s = elft->sHeaders[0];
	s = &s[shn];
	//kindSectionType(2);
	if (shn == SHN_COMMON)
		return ('C');
	else if (shn == SHN_ABS)
		return ((stb == STB_WEAK) ? 'A' : 'a');
	else
	{
		if (stb == STB_WEAK)
			return ('W');
		if (s->type == SHT_NOBITS && (s->flags & (SHF_ALLOC|SHF_WRITE)))
			return ((stb == STB_LOCAL) ? 'b' : 'B');
		else if (s->type == SHT_DYNAMIC || s->type == SHT_FINI_ARRAY || s->type == SHT_INIT_ARRAY)
			return ((stb == STB_WEAK) ? 'D' : 'd');
		else if (s->type == SHT_PROGBITS)
		{
			if (s->flags & SHF_EXECINSTR)
				return ((stb == STB_LOCAL) ? 't' : 'T');
			else if (s->flags & SHF_WRITE)
				return ((stb == STB_LOCAL) ? 'd' : 'D');
			else if (s->flags & SHF_ALLOC)
				return ((stb == STB_LOCAL) ? 'r' : 'R');
		}
	}
	// if elft_get_symbol_name == __abi_tag <=> 'r'
	return ('?');
}

inline char*	elft_get_section_name(t_elf* elft, t_elf_section_header* section_header)
{
	return (elft_get_shstrtab(elft) + section_header->name_offset);
}

inline char*	elft_get_shstrtab(t_elf* elft)
{
	t_elf_raw*	raw = elft_get_raw(elft);

	return (raw->data + (&(elft->sHeaders[0])[elft->header->sections_names_index])->offset);
}

inline char*	elft_get_specific_section(t_elf* elft, unsigned int elftsh_flag, t_elf_section_header* section)
{
	t_elf_raw*	raw = elft_get_raw(elft);
	t_elf_section_header*	_section = elft_inspect_section_header(elft, elftsh_flag, section);
	
	if (!_section)
		return (NULL);
	return (raw->data + _section->offset);
}
