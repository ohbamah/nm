/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elft_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:17:17 by ymanchon          #+#    #+#             */
/*   Updated: 2025/01/22 18:28:30 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elft.h"

inline t_elf_raw*	elft_get_raw(t_elf* elft)
{
	return (((t_elf_raw*)elft->__p));
}

static inline int	file_size(int fd)
{
	struct stat	statbuffer;
	fstat(fd, &statbuffer);
	return (statbuffer.st_size);
}

static inline void	set_errcode(int errval, int* __restrict__ error_code)
{
	if (error_code)
		*error_code = errval;
}

t_elf*	elft_init(int fd, int prot_flags, int* __restrict__ errc)
{
	if (fd == -1)
		return (set_errcode(ELFT_INVALID_FD, errc),
				NULL);
	t_elf*	elft = ft_calloc(1, sizeof(t_elf));
	elft->__p = malloc(sizeof(t_elf_raw));
	if (!elft)
		return (set_errcode(ELFT_MALLOC_FAILED, errc),
				NULL);
	t_elf_raw*	raw = elft_get_raw(elft);
	elftByteU*	magicn = mmap(NULL, 4, PROT_READ, MAP_SHARED, fd, 0);
	if (magicn <= 0)
		return (set_errcode(ELFT_MMAP_FAILED, errc),
				free(elft->__p), free(elft), NULL);
	else if (!isELF(magicn))
		return (set_errcode(ELFT_INVALID_FILE_FORMAT, errc),
				free(elft->__p), free(elft), NULL);
	munmap(magicn, 4);
	raw->data_size = file_size(fd);
	raw->data = mmap(NULL, raw->data_size, prot_flags, MAP_SHARED, fd, 0);
	if (raw->data <= 0)
		return (set_errcode(ELFT_MMAP_FAILED, errc),
				elft_destroy(elft), NULL);
	set_errcode(ELFT_SUCCESS, errc);
	return (elft);
}

int	elft_destroy(t_elf* elft)
{
	if (elft)
	{
		t_elf_raw*	raw = elft_get_raw(elft);
		if (elft->pHeaders)
			free(elft->pHeaders);
		if (elft->sHeaders)
			free(elft->sHeaders);
		free(elft);
		char*	data = raw->data;
		int		data_size = raw->data_size;
		free(raw);
		return (munmap(data, data_size));
	}
	return (0);
}
