/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 02:18:45 by bama              #+#    #+#             */
/*   Updated: 2025/01/21 02:55:01 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "libft.h"

static void	set_all_to_one(t_nm_options* options)
{
	for (unsigned long i = 0 ; i < sizeof(t_nm_options) / sizeof(int) ; ++i)
		((int*)options)[i] = 1;
}

void	ft_nm_options(int* ac_start_index, t_nm_options* options, int ac, char** av)
{
	int	i = 1;
	for ( ; i < ac && av[i][0] == '-' ; ++i)
	{
		if (av[i][1] == '-')
		{
			if (!ft_strcmp(av[i], "--all"))
				set_all_to_one(options);
			else if (!ft_strcmp(av[i], "--section-headers"))
				options->section_headers = 1;
			else if (!ft_strcmp(av[i], "--program-headers"))
				options->program_headers = 1;
			else if (!ft_strcmp(av[i], "--header"))
				options->header = 1;
		}
		else
		{
			int	option_len = ft_strlen(&av[i][1]);
			for (int j = 1 ; j <= option_len ; ++j)
			{
				if (!ft_strncmp(&av[i][j], "a", 1))
				{
					set_all_to_one(options);
					break ;
				}
				else if (!ft_strncmp(&av[i][j], "h", 1))
					options->header = 1;
				else if (!ft_strncmp(&av[i][j], "P", 1))
					options->program_headers = 1;
				else if (!ft_strncmp(&av[i][j], "S", 1))
					options->section_headers = 1;
			}
		}
	}
	*ac_start_index = i;
	//ft_printf("header : %d\n", options->header);
	//ft_printf("program header : %d\n", options->program_headers);
	//ft_printf("section header : %d\n", options->section_headers);
}
