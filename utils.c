/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 23:15:22 by bama              #+#    #+#             */
/*   Updated: 2025/01/21 03:31:34 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "libft.h"

void	nm_print_header_info(const t_nm_generic_header* __restrict__ header, int size)
{
	ft_printf("\t\e[1mEN-TÊTE:\e[0m\n");
	if (size == sizeof(t_elf32_header) || size == sizeof(t_elf64_header))
	{
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
	}
}

inline void	init_nm_struct(t_nm* nm_s, char* file)
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
		// Cast des données sur le header
	nm_s->bin_header.elf64 = (t_elf64_header*)nm_s->data;
	nm_s->bin_header.bits = ELFbits(nm_s->bin_header.elf64->identification_field.bits_archi);
	if (nm_s->bin_header.bits == 32)
		nm_s->bin_header.elf32 = (t_elf32_header*)nm_s->data;
		//Todo: Cast des données de sections/segments vers une structure appropriée
	//nm_s->bin_segment/section = (t_elf64/32_segment/section*)(nm_s->data + nm_s->bin_header.elf64/32->header_size);
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
