/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:38:24 by bama              #+#    #+#             */
/*   Updated: 2025/03/15 17:39:48 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

# include "elft/elft.h"
# include "libft/libft.h"
# include <fcntl.h>

# define CMP_FUN(name)	int	cmpf_##name(t_elf_symfinder* a, t_elf_symfinder* b)

typedef	int	(*cmpf)(t_elf_symfinder*, t_elf_symfinder*);

CMP_FUN(alpha_g);
CMP_FUN(alpha_ng);
CMP_FUN(addr_g);
CMP_FUN(addr_ng);

#endif
