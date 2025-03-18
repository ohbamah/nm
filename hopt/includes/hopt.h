
#ifndef HOPT_H
#define HOPT_H

# define HOPT_ALIGN_STRUCT		_Pragma("pack(push, 1)")
# define HOPT_ALIGN_STRUCT_END	_Pragma("pack(pop)")

# define HOPT_MALLOC_FAILED		1
# define HOPT_OPTAC_INVALID		2

// Error code to specify error (look at 'hopt_opt' to see which option is causing the error)
extern int		hopt_err;
// The option that refers to the error stored in 'hopt_err'
extern char		hopt_opt[16];

// Parse and interpret options for you :0
//
// @param ac Arguments' program count
// @param av Total arguments's program
// @param buffer Your buffer to stock validation
// @param optstr The options strings (in order of buffer bytes)
// @param optargcount The arguments options can handling (nullable if all options have ZERO arg)
int		hopt(int ac, char** av, void* buffer, const char* restrict optstr, const char* restrict optargcount);

// Allow invalid option and not occur an error
void	hopt_allow_unknow();

// Only if 'hopt_allow_unknow()' was called
// Sort unknown like known options
void	hopt_sort_unknow();

// Return a string for the (potential) current error
// (needs to free)
char*	hopt_strerror(void);

#endif
