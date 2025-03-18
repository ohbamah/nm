#include "__hopt_.h"
#include "hopt.h"

int		hopt_err = 0; // extern global var in 'hopt.h'
char	hopt_opt[16] = {0};

BOOL	hopt_unknow_allowed = FALSE;
BOOL	hopt_unknow_sorted = FALSE;

static inline
int
check_first_mallocs(char***restrict opts, char***restrict optac)
{
	if (!*opts)
	{
		if (optac)
			free2((void**)optac);
		hopt_err = HOPT_MALLOC_FAILED;
		return (-1);
	}
	return (0);
}

// [LINKER] link OPTSTR and OPTARGCOUNT in OPTORDER
static
void
LINKER(/*const*/ char** opts, /*const*/ char** optac, unsigned int** optorder, unsigned int** offsettab)
{
	BOOL	found = FALSE;
	if (optac)
	{
		unsigned int	offset = 0;
		for (unsigned int i = 0 ; opts[i] ; ++i)
		{
			char**			op = strsplit(opts[i], '=');
			for (unsigned int j = 0 ; op[j] ; ++j)
			{
				for (unsigned int g = 0 ; optac[g] && found == FALSE ; ++g)
				{
					char**  oc = strsplit(optac[g], ':');
					if (!strcmp(op[j], oc[0]))
					{
						int value = 0;
						if (oc[1])
							value = atoi(oc[1]);
						(*optorder)[i] = value;
						(*offsettab)[i] = offset;
						if (value == 0)
							++offset;
						else if (value > 0)
							offset += value * sizeof(char*);
						found = TRUE;
					}
					free2((void**)oc);
				}
				free(op[j]);
			}
			if (found == FALSE)
			{
				(*offsettab)[i] = offset;
				++offset;
			}
			found = FALSE;
			free(op);
			//printf("v:%d|off:%d\n", (*optorder)[i], (*offsettab)[i]);
		}
	}
	else
		for (unsigned int i = 0 ; opts[i] ; ++i)
		(*offsettab)[i] = i;
}

// [FINDER] find options
static
unsigned int
FINDER(int ac, /*const*/ char** av, /*const*/ char** opts, /*const*/ unsigned int* optorder, /*const*/ unsigned int* offsettab, void* restrict buffer)
{
	unsigned int	count = 0;
	BOOL			error = FALSE;
	BOOL			found = FALSE;
	for (unsigned int i = 0 ; error == FALSE && i < (unsigned int)ac ; ++i)
	{
		found = FALSE;
		if (!strncmp("-", av[i], 1) && strnlen(av[i], 2) == 2)
		{
			for (unsigned int j = 0 ; error == FALSE && opts[j] ; ++j)
			{
				char**	op = strsplit(opts[j], '=');
				for (unsigned int g = 0 ; error == FALSE && op[g] ; ++g)
				{
					if (found == FALSE && !strcmp(op[g], &av[i][1]))
					{
						unsigned int k = i;
						for (unsigned int h = 0 ; error == FALSE && i - k < optorder[j] ; ++i, ++h)
						{
							if (!av[i + 1])
							{
								hopt_err = HOPT_OPTAC_INVALID;
								strncpy(hopt_opt, op[g], strlen(op[g]));
								error = TRUE;
							}
							else
							{
								char*	strtmp = strdup(av[i + 1]);
								memcpy(&((char*)buffer)[offsettab[j] + h * sizeof(char*)], &strtmp, sizeof(char*));
							}
							++count;
						}
						if (k == i)
							((char*)buffer)[offsettab[j]] = (char)1;
					}
					free(op[g]);
				}
				//	printf("offset %u\n", offsettab[j]);
				free(op);
			}
		}
	}
	return (count);
}

// re-SORT av tab strings
//static
//void
//SORT(int ac, /*const*/ char** av, )
//{
//
//}

// Parse and interpret options for you :0
//
// @param ac Arguments' program count
// @param av Total arguments's program
// @param buffer Your buffer to stock validation
// @param optstr The options strings (in order of buffer bytes)
// @param optargcount The arguments options can handling (nullable if all options have ZERO arg)
int
hopt(int ac, char** av, void* restrict buffer, const char* restrict optstr, const char* restrict optargcount)
{
	unsigned int	count		= 0;							// total count of parsed option(s)
	unsigned int	optcount	= 0;							// total count of options
	unsigned int*	optorder	= NULL;							// the option args count table	(refer each option by their arguments count)
	unsigned int*	offsettab	= NULL;							// the offset table (refer each option with his offset)
	char**			opts		= strsplit(optstr, '/');		// options
	char**			optac		= strsplit(optargcount, '/');	// option arguments count

	if (check_first_mallocs(&opts, &optac) == -1)
		return (-1);
	optcount = strlen2(opts);
	optorder = calloc(optcount, sizeof(int)); //! --> turn into MALLOC
	offsettab = calloc(optcount, sizeof(int)); //! --> turn into MALLOC
	if (optorder)
	{
		LINKER(opts, optac, &optorder, &offsettab);
		count = FINDER(ac, av, opts, optorder, offsettab, buffer);
		//SORT(ac, av, count);
	}
	else
		hopt_err = HOPT_MALLOC_FAILED;
	free(offsettab);
	free(optorder);
	free2((void**)opts);
	free2((void**)optac);
	if (hopt_err != 0)
		return (-1);
	return (count);
}

// Allow invalid option and not occur an error
void
hopt_allow_unknow()
{
	hopt_unknow_allowed = TRUE;
}

// Only if 'hopt_allow_unknow()' was called
// Sort unknown like known options
void
hopt_sort_unknow()
{
	hopt_unknow_sorted = TRUE;
}

// Return a string for the (potential) current error
// (needs to free)
char*
hopt_strerror(void)
{
	char*	test;

	switch (hopt_err)
	{
		case HOPT_MALLOC_FAILED:
			test = malloc((21 + 1) * sizeof(char));
			strncpy(test, "hopt: malloc failed.", 21);
			test[21] = 0;
			return (test);
		case HOPT_OPTAC_INVALID:
			test = malloc((14 + 20 + strlen(hopt_opt) + 1) * sizeof(char));
			snprintf(test, 14 + 20 + strlen(hopt_opt), "hopt: option -%s arg count invalid.", hopt_opt);
			return (test);
		default:
			test = malloc((15 + 1) * sizeof(char));
			strncpy(test, "hopt: success.", 15);
			test[15] = 0;
			return (test);
	}
}
