/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:32:04 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/23 00:55:01 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	handle_options(const t_nm* nm_s, t_nm_options options)
{
	if (options.header)
		elft_debug_header(nm_s->elf->header);
	if (options.section_headers)
		elft_debug_section_headers(nm_s->elf, nm_s->elf->header->section_headers_count);
	//if (options.program_headers)
	//	elft_debug_program_headers(nm_s->elf->pHeaders, nm_s->elf->header->program_headers_count);
}

static void	ft_nm_body(const t_nm* nm_s)
{
	int		strtab_size;
	char*	strtab = elft_get_strtab_section(nm_s->elf, &strtab_size);
	t_elf_section_header* sym_header = elft_inspect_section_header(nm_s->elf, ELFTSH_SYMBOL, NULL);
	t_elf_symbol*	sym = elft_jump_to_symbol(elft_get_raw(nm_s->elf)->data, sym_header);
	t_elf_symbol*	tmp_sym;
	for (int i = 0 ; i < sym_header->size / sizeof(t_elf_symbol) ; ++i)
	{
		tmp_sym = &sym[i];
		if ((unsigned long)(strtab + tmp_sym->name_offset) >= (unsigned long)(strtab + strtab_size))
			continue ;
		if (tmp_sym->value > 0)
			ft_printf("%p", tmp_sym->value);
		else
			ft_printf("\t");	
		ft_printf("\t%s\n", strtab + tmp_sym->name_offset);
	}
}

static void	ft_nm(char* file, t_nm_options options)
{
	t_nm	nm_s = {0};
	t_elf*	elft;

	int	fd = open(file, O_RDONLY);
	elft = elft_init(fd, PROT_READ, &nm_s._err);
	nm_s.elf = elft;
	if (!handle_errors(&nm_s, NM_INIT))
		return ;

	elft_read_header(elft);
	elft_read_program_headers(elft);
	elft_read_section_headers(elft);
	handle_options(&nm_s, options);
	ft_nm_body(&nm_s);

	nm_s._err = elft_destroy(elft);
	handle_errors(&nm_s, NM_DESTROY);
	close(fd);
}

int	main(int ac, char** av)
{
	int	i = 1;
	t_nm_options	options = {0};
	ft_nm_options(&i, &options, ac, av);
	if (ac - i > 0)
	{
		int	i_start = i;
		for ( ; i < ac ; ++i)
		{
			if (ac - i_start > 1)
				ft_printf("\e[1;36m%s:\e[0m\n", av[i]);
			ft_nm(av[i], options);
			if (ac - i_start > 1)
				write(STDOUT_FILENO, "\n", 1);
		}
	}
	else
		ft_nm("a.out", options);
	return (0);
}
