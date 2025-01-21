/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:41:43 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/21 16:00:16 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "libft.h"

// ?Segments --> informations nécessaires à l'exécution du programme
// ?Sections --> informations pour la résolution des liens (entre fonctions et le remplacement des données)

// Mettre dans le fd=2(STDERR_FILENO) la sortie quand il y a une erreur
// Mapper sur plusieurs pages lorsque la taille depasse la PAGE_SIZE
// Supporter le 32 bits

static void	handle_options(t_nm* nm_s, t_nm_options options)
{
	if (options.header)
	{
		if (nm_s->elf_headers.bits == 32)
			nm_print_header_info((t_nm_generic_header*)nm_s->elf_headers.h32b, NM_ELF_HEADER);
		else if (nm_s->elf_headers.bits == 64)
			nm_print_header_info((t_nm_generic_header*)nm_s->elf_headers.h64b, NM_ELF_HEADER);
	}
	if (options.program_headers)
	{
		if (nm_s->elf_headers.bits == 32)
			nm_print_header_info((t_nm_generic_header*)nm_s->elf_headers.program_h32b, NM_PROGRAM_HEADER);
		else if (nm_s->elf_headers.bits == 64)
			nm_print_header_info((t_nm_generic_header*)nm_s->elf_headers.program_h64b, NM_PROGRAM_HEADER);
	}
	if (options.section_headers)
	{
		if (nm_s->elf_headers.bits == 32)
			nm_print_header_info((t_nm_generic_header*)nm_s->elf_headers.section_h32b, NM_SECTION_HEADER);
		else if (nm_s->elf_headers.bits == 64)
			nm_print_header_info((t_nm_generic_header*)nm_s->elf_headers.section_h64b, NM_SECTION_HEADER);
	}
}

static void	ft_nm_body(t_nm* nm_s, t_nm_options options)
{
	handle_options(nm_s, options);
}

static void	ft_nm(char* file, t_nm_options options)
{
	t_nm	nm;
	init_nm_struct(&nm, file);
	if (handle_errors(nm, NM_INIT))
		ft_nm_body(&nm, options);
	destroy_nm_struct(&nm);
	handle_errors(nm, NM_DESTROY);
}

int	main(int ac, char** av)
{
	int	i = 1;
	t_nm_options	options = {0};
	ft_nm_options(&i, &options, ac, av);
	for ( ; i < ac ; ++i)
	{
		ft_printf("\e[1;34m%s:\e[0m\n", av[i]);
		ft_nm(av[i], options);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
