/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elft_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:10:16 by bama              #+#    #+#             */
/*   Updated: 2025/01/26 16:22:45 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elft.h"

t_elf_sections_lst*	elft_init_sections_lst(t_elf* elft, unsigned int elftsh_flag)
{
	t_elf_sections_lst*		root = NULL;
	t_elf_section_header*	header = NULL;
	t_elf_section_header*	tmp_header = NULL;
	while ((header = elft_inspect_section_header(elft, elftsh_flag, header)))
	{
		char* data = elft_get_specific_section(elft, elftsh_flag, tmp_header);
		if (!data)
			return (root);
		tmp_header = header;
		root = elft_add_node_lst(root, elft_create_node_lst(data, header));
	}
	return (root);
}

t_elf_sections_lst*	elft_add_node_lst(t_elf_sections_lst* root, t_elf_sections_lst* node)
{
	if (!node)
		return (root);
	node->next = root;
	return (node);
}

t_elf_sections_lst*	elft_create_node_lst(char* data, t_elf_section_header* header)
{
	t_elf_sections_lst*	new;

	new = malloc(sizeof(t_elf_sections_lst));
	if (!new)
		return (NULL);
	new->header = header;
	new->data = data;
	new->next = NULL;
	return (new);
}

void	elft_destroy_lst(t_elf_sections_lst* root)
{
	t_elf_sections_lst*	tmp = root;

	while (root)
	{
		tmp = root;
		root = root->next;
		free(tmp);
	}
}
