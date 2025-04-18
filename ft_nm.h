/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:38:24 by bama              #+#    #+#             */
/*   Updated: 2025/03/18 18:26:29 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

# include "elft/elft.h"
# include <stdbool.h>
# include "libft/libft.h"
# include "hopt/hopt.h"
# include <fcntl.h>

# define CMP_FUN(name)	int	cmpf_##name(t_elf_symfinder* a, t_elf_symfinder* b)

typedef	int	(*cmpf)(t_elf_symfinder*, t_elf_symfinder*);

typedef struct nm_options
{
	bool	sys_debug;		// a
	bool	only_extern;	// g
	bool	only_undef;		// u
	bool	only_def;		// U
	bool	reverse_sort;	// r
	bool	no_sort;		// p
}	t_nm_options;

CMP_FUN(alpha_g);
CMP_FUN(alpha_ng);
CMP_FUN(addr_g);
CMP_FUN(addr_ng);

#endif
