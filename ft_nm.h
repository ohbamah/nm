/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:40:38 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/20 17:41:37 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

# define NM_SUCCESS		0
# define NM_FAILED_MMAP		1
# define NM_FAILED_MUNMAP	2
# define NM_FAILED_OPEN		3
# define NM_FAILED_CLOSE	4

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/mman.h>

typedef struct s_nm
{
	int		_err;
	int		fd;
	unsigned long	bin_size;
	char*		bin;
}	t_nm;

#endif
