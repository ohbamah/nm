/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 23:15:22 by bama              #+#    #+#             */
/*   Updated: 2025/01/21 15:57:42 by ymanchon         ###   ########.fr       */
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
		nm_s->elf_headers.program_h32b = (t_elf32_program_header*)(nm_s->data + nm_s->elf_headers.h32b->header_table_offset);
		nm_s->elf_headers.section_h32b = (t_elf32_section_header*)(nm_s->data + nm_s->elf_headers.h32b->sections_table_offset);
	}
	else
	{
		nm_s->elf_headers.program_h64b = (t_elf64_program_header*)(nm_s->data + nm_s->elf_headers.h64b->header_table_offset);
		nm_s->elf_headers.section_h64b = (t_elf64_section_header*)(nm_s->data + nm_s->elf_headers.h64b->sections_table_offset);
	}
		//Todo: Cast des données de sections/segments vers une structure appropriée
	//nm_s->bin_segment/section = (t_elf64/32_segment/section*)(nm_s->data + nm_s->bin_header.elf64/32->header_size);
	//printf("$%s$\n", (char*)(nm_s->data + nm_s->elf_headers.h64b->sections_table_offset));
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
