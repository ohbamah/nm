#include "ft_nm.h"

// local	-> lowercase
// global	-> uppercase (no 'u', 'v' and 'w')
char	elft_get_sym_type(t_elf* elft, t_elf_symfinder* symf)
{
	//char	stt = sym->info & 0xF;	// type
	t_elf_symbol*	sym = symf->sym;
	char			stb = sym->info >> 4;	// linking (binding)
	int				shn = sym->index;		// index

	if (!ft_strcmp(symf->name, "__abi_tag"))
		return ('r');
	if (shn == SHN_UNDEF)
		return ((stb == STB_WEAK) ? 'w' : 'U');
	t_elf_section_header* s = elft->sHeaders[0];
	s = &s[shn];
	if (shn == SHN_COMMON)
		return ('C');
	else if (shn == SHN_ABS)
		return ((stb == STB_WEAK) ? 'A' : 'a');
	else
	{
		if (stb == STB_WEAK)
			return ('W');
		if (s->type == SHT_NOBITS && (s->flags & (SHF_ALLOC|SHF_WRITE)))
			return ((stb == STB_LOCAL) ? 'b' : 'B');
		else if (s->type == SHT_DYNAMIC || s->type == SHT_FINI_ARRAY || s->type == SHT_INIT_ARRAY)
			return ((stb == STB_WEAK) ? 'D' : 'd');
		else if (s->type == SHT_PROGBITS)
		{
			if (s->flags & SHF_EXECINSTR)
				return ((stb == STB_LOCAL) ? 't' : 'T');
			else if (s->flags & SHF_WRITE)
				return ((stb == STB_LOCAL) ? 'd' : 'D');
			else if (s->flags & SHF_ALLOC)
				return ((stb == STB_LOCAL) ? 'r' : 'R');
		}
		else if (s->type == SHT_MIPS_DEBUG || s->type == SHT_ALPHA_DEBUG || s->type == SHT_MIPS_XLATE_DEBUG)
			return ((stb == STB_LOCAL) ? 'n' : 'N');
	}
	return ('?');
}

void	print_tab(t_elf* elft, t_elf_symfinder** tab, int n)
{
	int	i = -1;
	while (++i < n)
	{
		char	type = elft_get_sym_type(elft, tab[i]);
		if (tab[i]->name && ft_strlen(tab[i]->name) > 1 && type != 'a')
		{
			char	format[23];
			if (type == 'U')
				ft_strlcpy(format, "% 17c \e[1m%c\e[0m %s\n", 23);
			else
				ft_strlcpy(format, "%016llx \e[1m%c\e[0m %s\n", 23);
			printf(format, tab[i]->sym->value, type, tab[i]->name);
		}
	}
}

void	sort_tab(t_elf_symfinder*** tab, int n, cmpf fun)
{
	t_elf_symfinder**	temp = *tab;
	int					i = 0;
	int					j;
	int					g;

	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			if (fun(temp[i], temp[j]))
				ft_swap_addr((void**)&temp[i], (void**)&temp[j]);
			++j;
		}
		++i;
	}

	*tab = temp;
}

void	ft_nm(char* file_name)
{
	int		fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("%sFichier inexistant (ou invalide)%s\n", "\e[31m", "\e[0m");
		return ;
	}
	t_elf*	elft = elft_init(fd, PROT_READ);
	elft_read_header(elft);
	elft_read_section_headers(elft);
	elft_read_shstrtab(elft);
	elft_free_shfinder(elft_find_sectionH_by_name(elft, ".symtab"));
	if (elft->err == ELFT_SHEADER_NOT_EXIST)
	{
		printf("%sAucun symbole trouvé%s\n", "\e[31m", "\e[0m");
		elft_destroy(elft);
		return ;
	}

	// find symboles
	t_elf_symfinder*	test = elft_find_next_sym(elft);
	while (test)
	{
		elft_free_symfinder(test);
		test = elft_find_next_sym(elft);
	}

		// stock symboles
	int	i = 0;
	int	n = elft_find__get_next_sym_count();
	t_elf_symfinder**	sf = malloc(n * sizeof(t_elf_symfinder*));
	elft_find__reset_next_sym_count();
	while (i < n)
		sf[i++] = elft_find_next_sym(elft);

		// nm
	sort_tab(&sf, n, cmpf_alpha_g);
	print_tab(elft, sf, n);

		// terminate
	i = 0;
	while (i < n)
		elft_free_symfinder(sf[i++]);
	free(sf);
	elft_destroy(elft);
	close(fd);
}

int	main(int ac, char** av)
{
		// program initialisation
	if (!av[1])
		return (1);

	t_nm_options	opt;
	memset(&opt, 0, sizeof(t_nm_options));
	hopt(ac, av, &opt, "c", "c:1");	

	printf("count : %s\n", opt.count);
	int	i = 1;
	while (i < ac )
	{
		if (ac > 2)
			ft_printf("\e[1;45m%s:\e[0m\n", av[i]);
		ft_nm(av[i]);
		if (ac > 2)
			write(STDOUT_FILENO, "\n", 1);
		++i;
	}
	return (0);
}