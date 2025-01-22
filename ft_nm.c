/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:32:04 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/22 17:49:16 by ymanchon         ###   ########.fr       */
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
