#ifndef DEBUG_H
#define DEBUG_H

#include "libft.h" // ft_printf

#ifdef VERBOSE
	#define LOG(format, ...) ft_printf(format, __VA_ARGS__)
#else
	#define LOG(format, ...)
#endif

#endif // DEBUG_H
