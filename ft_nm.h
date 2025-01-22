/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:15:50 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/22 17:48:47 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

# define NM_INIT			-1
# define NM_DESTROY			1

# define NM_ELFT_DESTRUCT_FAILED	-2
# define NM_CLOSE_FAILED			-1

# ifndef PAGESIZE
#  define PAGESIZE	_SC_PAGE_SIZE
# endif

# include "libft.h"
# include "elft.h"

typedef struct s_nm_options
{
	int	header;
	int	section_headers;
	int	program_headers;
	//int	segment_names;
}	t_nm_options;

typedef struct s_nm
{
	int		_err;
	t_elf*	elf;
}	t_nm;

void	ft_nm_options(int* ac_start_index, t_nm_options* options, int ac, char** av);
int		handle_errors(const t_nm* nm_s, int flag);

#endif
