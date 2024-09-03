#ifndef DEBUG_H
#define DEBUG_H

#include "libft.h" // ft_printf
#include <stdint.h> // uintptr_t
#include "zone.h"

#ifdef VERBOSE
	#define LOG(format, ...) ft_printf(format, __VA_ARGS__)
#else
	#define LOG(format, ...)
#endif

size_t show_alloc_mem_zone(zone_t *zone);

#endif // DEBUG_H
