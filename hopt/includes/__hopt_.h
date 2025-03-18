#ifndef __HOPT__H
#define __HOPT__H

# define _XOPEN_SOURCE 700
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define BOOL	char
# define TRUE	1
# define FALSE	0

char**			strsplit(const char* restrict s, char sep);
void			free2(void**  ptr2);
unsigned int	strlen2(char* restrict* restrict s);

#endif
