#ifndef DEBUG_H
#define DEBUG_H

#include "libft.h" // ft_printf
#include "zone.h"

#include <stdint.h> // uintptr_t

#if VERBOSE
	#define LOG(format, ...) ft_printf(format, __VA_ARGS__)
#else
	#define LOG(format, ...)
#endif

#define MALLOC_SCRIBBLE_VALUE 0x55;
#define MALLOC_PRESCRIBBLE_VALUE 0xAA;

#ifndef MALLOC_SCRIBBLE
	#define MALLOC_SCRIBBLE 0
#endif

#ifndef MALLOC_PRESCRIBBLE
	#define MALLOC_PRESCRIBBLE 0
#endif

size_t show_alloc_mem_zone(zone_t *zone);
void   show_alloc_mem_hex(zone_t *zone);

#endif // DEBUG_H
