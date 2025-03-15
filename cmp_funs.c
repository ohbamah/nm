/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_funs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:38:43 by bama              #+#    #+#             */
/*   Updated: 2025/03/15 17:48:29 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

CMP_FUN(alpha_g);
CMP_FUN(alpha_ng);
CMP_FUN(addr_g);
CMP_FUN(addr_ng);

CMP_FUN(alpha_g)
{
	return (ft_strcmp(a->name, b->name) < 0);
}

CMP_FUN(alpha_ng)
{
	return (ft_strcmp(a->name, b->name) > 0);
}

CMP_FUN(addr_g)
{
	return (a->sym->value < b->sym->value);
}

CMP_FUN(addr_ng)
{
	return (a->sym->value > b->sym->value);
}
