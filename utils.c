/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 23:15:22 by bama              #+#    #+#             */
/*   Updated: 2025/01/21 19:05:01 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "libft.h"

inline static void	setup_32_or_64b_headers(t_nm* nm_s)
{
	nm_s->elf_headers.h64b = (t_elf64_header*)nm_s->data;
	nm_s->elf_headers.bits = ELFbits(nm_s->elf_headers.h64b->identification_field.bits_archi);
	if (nm_s->elf_headers.bits == 32)
	{
		nm_s->elf_headers.h32b = (t_elf32_header*)nm_s->data;
		nm_s->elf_headers.program_h32b = (t_elf32_program_header**)malloc(nm_s->elf_headers.h32b->program_headers_count * sizeof(t_elf32_program_header*)); // !check malloc
		nm_s->elf_headers.section_h32b = (t_elf32_section_header**)malloc(nm_s->elf_headers.h32b->section_headers_count * sizeof(t_elf64_section_header*)); // !check malloc
		nm_s->elf_headers.program_h32b[0] = (t_elf32_program_header*)(nm_s->data + nm_s->elf_headers.h32b->program_headers_offset);
		nm_s->elf_headers.section_h32b[0] = (t_elf32_section_header*)(nm_s->data + nm_s->elf_headers.h32b->section_headers_offset);
	}
	else
	{
		nm_s->elf_headers.program_h64b = (t_elf64_program_header**)malloc(nm_s->elf_headers.h64b->program_headers_count * sizeof(t_elf64_program_header*)); // !check malloc
		nm_s->elf_headers.section_h64b = (t_elf64_section_header**)malloc(nm_s->elf_headers.h64b->section_headers_count * sizeof(t_elf64_section_header*)); // !check malloc
		for (int i = 0 ; i < nm_s->elf_headers.h64b->program_headers_count || i < nm_s->elf_headers.h64b->section_headers_count ; ++i)
		{
			if (i < nm_s->elf_headers.h64b->program_headers_count)
				nm_s->elf_headers.program_h64b[i] = (t_elf64_program_header*)(nm_s->data + nm_s->elf_headers.h64b->program_headers_offset + sizeof(t_elf64_program_header) * i);
			if (i < nm_s->elf_headers.h64b->section_headers_count)
				nm_s->elf_headers.section_h64b[i] = (t_elf64_section_header*)(nm_s->data + nm_s->elf_headers.h64b->section_headers_offset + sizeof(t_elf64_section_header) * i);
		}
	}
	t_elf64_section_header*	test = (t_elf64_section_header*)findAddressOfSectionType(FT_ELF_STRING_TABLE, (t_nm_generic_header**)nm_s->elf_headers.section_h64b, nm_s->elf_headers.h64b->section_headers_count, nm_s->elf_headers.bits);
	if (test <= 0)
		return ;
	char*	string_table = nm_s->data + test->offset + 1;
	unsigned long i = 0;
	char *current_string = string_table;
    while (i < test->size)
	{
        printf("Chaîne dans la table : %x--> %s\n", test->VAddress_of_section + i, current_string);
        // Avancer jusqu'à la chaîne suivante (en sautant au caractère nul)
		i += ft_strlen(current_string) + 1;
        current_string += ft_strlen(current_string) + 1;
    }
}

void	init_nm_struct(t_nm* nm_s, char* file)
{
		// Mise à zéro des bits
	ft_memset(nm_s, 0, sizeof(t_nm));
		// Ouverture fichier
	nm_s->fd = open(file, O_RDONLY);
	if (nm_s->fd == -1)
	{
		nm_s->_err = NM_FAILED_OPEN;
		return ;
	}
		// Premier mmap (ELF check format)
	nm_s->data = mmap(NULL, 4 * sizeof(char), PROT_READ, MAP_SHARED, nm_s->fd, 0);
	if (!isELF((nmByte8U*)nm_s->data))
	{
		nm_s->_err = NM_FAILED_NO_ELF;
		nm_s->data_size = 4 * sizeof(char);
		return ;
	}
		// Second mmap (prise contenu fichier)
	struct stat	bufstat;
	fstat(nm_s->fd, &bufstat);
	nm_s->data_size = bufstat.st_size;
	nm_s->data = mmap(NULL, nm_s->data_size, PROT_READ, MAP_SHARED, nm_s->fd, 0);
	if (!nm_s->data || nm_s->data == MAP_FAILED)
	{
		nm_s->_err = NM_FAILED_MMAP;
		return ;
	}
		// Sans erreur
	nm_s->_err = NM_SUCCESS;
	setup_32_or_64b_headers(nm_s);
}

inline void	destroy_nm_struct(t_nm *nm_s)
{
	if (nm_s->data > (char*)0)
		if (munmap(nm_s->data, nm_s->data_size) == -1)
			nm_s->_err = NM_FAILED_MUNMAP;
	if (nm_s->fd != -1)
		if (close(nm_s->fd) == -1)
			nm_s->_err = NM_FAILED_CLOSE;
	if (nm_s->elf_headers.program_h64b)
		free(nm_s->elf_headers.program_h64b);
	if (nm_s->elf_headers.section_h64b)
		free(nm_s->elf_headers.section_h64b);
}

inline int	handle_errors(t_nm nm_s, int flag)
{
	if (flag == NM_INIT)
	{
		switch (nm_s._err)
		{
			case NM_FAILED_OPEN:
				ft_printf("\t\e[1;41mNo such file\e[0m\n");
				return (0);
			case NM_FAILED_MMAP:
				ft_printf("\t\e[1;41mMemory error, failed to map object file\e[0m\n");
				return (0);
			case NM_FAILED_NO_ELF:
				ft_printf("\t\e[1;31mCan not see any details about this file because is not an object/ELF file\n\e[0m");
				return (0);
			default:
				break ;
		}
	}
	else if (flag == NM_DESTROY)
	{
		switch (nm_s._err)
		{
			case NM_FAILED_MUNMAP:
				ft_printf("\t\e[1;41mMemory error, failed to unmap object file\e[0m\n");
				return (0);
			case NM_FAILED_CLOSE:
				ft_printf("\t\e[1;41mFile system error, failed to close the opened file\e[0m\n");
				return (0);
		}
	}
	return (1);
}
