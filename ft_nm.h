/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:40:38 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/21 17:55:58 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

# define NM_INIT			-1
# define NM_DESTROY			1

# define NM_NO_SIZE			0

# define NM_SUCCESS			0
# define NM_FAILED_MMAP		1
# define NM_FAILED_MUNMAP	2
# define NM_FAILED_OPEN		3
# define NM_FAILED_CLOSE	4
# define NM_FAILED_NO_ELF	5

# define NM_ELF_HEADER		0
# define NM_PROGRAM_HEADER	1
# define NM_SECTION_HEADER	2

# ifndef PAGESIZE
#  define PAGESIZE	_SC_PAGE_SIZE
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include "ft_elf.h"

typedef struct s_nm_options
{
	int	header;
	int	section_headers;
	int	program_headers;
	//int	segment_names;
}	t_nm_options;

typedef struct s_nm
{
	int				_err;
	int				fd;
	unsigned long	data_size;
	char*			data;
	struct
	{
		int				bits;
		union
		{
			t_elf64_header*	h64b;
			t_elf32_header*	h32b;
		};
		union
		{
			t_elf64_program_header**	program_h64b;
			t_elf32_program_header**	program_h32b;
		};
		union
		{
			t_elf64_section_header**	section_h64b;
			t_elf32_section_header**	section_h32b;
		};
	}				elf_headers;
}	t_nm;

void	ft_nm_options(int* ac_start_index, t_nm_options* options, int ac, char** av);
void	init_nm_struct(t_nm* nm_s, char* file);
void	destroy_nm_struct(t_nm *nm_s);
int		handle_errors(t_nm nm_s, int flag);
void	nm_print_header_info(const t_nm_generic_header* __restrict__ header, int size, int flag);

#endif
