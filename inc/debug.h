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

int common_ptr_denominator_size(zone_t *zones);
void *reduce(void *ptr, int common);

void show(void);
void show_zone(zone_t *zone);
void mwrite(size_t min);
void write_strings(const char *str, size_t len, size_t min);
void sanitize(void);

size_t mem_total(void);
size_t mem_used(void);

#endif // DEBUG_H
