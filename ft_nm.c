/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:41:43 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/20 17:45:07 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "libft.h"

// Mettre dans le fd=2(STDERR_FILENO) la sortie quand il y a une erreur
// Mapper sur plusieurs pages lorsque la taille depasse la PAGE_SIZE

static inline void	init_nm_struct(t_nm* nm_s, char* file)
{
	nm_s->fd = open(file, O_RDONLY);
	if (nm_s->fd == -1)
	{
		nm_s->_err = NM_FAILED_OPEN;
		return ;
	}
	struct stat	bufstat;
	fstat(nm_s->fd, &bufstat);
	nm_s->bin_size = bufstat.st_size;
	nm_s->bin = mmap(NULL, nm_s->bin_size, PROT_READ, MAP_SHARED, nm_s->fd, 0);
	if (!nm_s->bin || nm_s->bin == MAP_FAILED)
		nm_s->_err = NM_FAILED_MMAP;
	else
		nm_s->_err = NM_SUCCESS;
}

static inline void	destroy_nm_struct(t_nm *nm_s)
{
	if (nm_s->bin > (char*)0)
		if (munmap(nm_s->bin, nm_s->bin_size) == -1)
			nm_s->_err = NM_FAILED_MUNMAP;
	if (nm_s->fd != -1)
		if (close(nm_s->fd) == -1)
			nm_s->_err = NM_FAILED_CLOSE;
}

static inline int	handle_errors(t_nm nm_s)
{
	switch (nm_s._err)
	{
		case NM_FAILED_OPEN:
			ft_printf("\t\e[1;41mNo such file\e[0m\n");
			return (0);
		case NM_FAILED_MMAP:
			ft_printf("\t\e[1;41mMemory error, failed to map object file\e[0m\n");
			return (0);
		case NM_FAILED_MUNMAP:
			ft_printf("\t\e[1;41mMemory error, failed to unmap object file\e[0m\n");
			return (0);
		case NM_FAILED_CLOSE:
			ft_printf("\t\e[1;41mFile system error, failed to close the opened file\e[0m\n");
			return (0);
		default:
			break ;
	}
	return (1);
}

void	ft_nm_body(t_nm* nm_s)
{
}

void	ft_nm(char* file)
{
	t_nm	nm;
	init_nm_struct(&nm, file);
	if (handle_errors(nm))
		ft_nm_body(&nm);
	destroy_nm_struct(&nm);
	handle_errors(nm);
}

int	main(int ac, char** av)
{
	for (int i = 1 ; i < ac ; ++i)
	{
		ft_printf("\e[1;34m%s:\e[0m\n", av[i]);
		ft_nm(av[i]);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
