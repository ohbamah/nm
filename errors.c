/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:32:51 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/22 16:25:25 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

inline int	handle_errors(const t_nm* nm_s, int flag)
{
	if (flag == NM_INIT)
	{
		switch (nm_s->_err)
		{
			case ELFT_INVALID_FD:
				ft_printf("\e[1;41mNo such file\e[0m\n");
				return (0);
			case ELFT_MMAP_FAILED:
				ft_printf("\e[1;41mMemory error, failed to map object file\e[0m\n");
				return (0);
			case ELFT_INVALID_FILE_FORMAT:
				ft_printf("\e[1;31mCan not see any details about this file because is not an object/ELF file\n\e[0m");
				return (0);
			default:
				break ;
		}
	}
	else if (flag == NM_DESTROY)
	{
		switch (nm_s->_err)
		{
			case NM_ELFT_DESTRUCT_FAILED:
				ft_printf("\e[1;41mMemory error, failed to unmap object file\e[0m\n");
				return (0);
			case NM_CLOSE_FAILED:
				ft_printf("\e[1;41mFile system error, failed to close the opened file\e[0m\n");
				return (0);
		}
	}
	return (1);
}
