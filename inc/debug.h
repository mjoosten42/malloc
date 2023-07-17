#ifndef DEBUG_H
#define DEBUG_H

#include "libft.h" // ft_printf
#include "zone.h"

#ifdef VERBOSE
	#define LOG(format, ...) ft_printf(format, __VA_ARGS__)
#else
	#define LOG(format, ...)
#endif

void show(void);
void show_zone(zone_t *zone);
void mwrite(size_t min);
void write_strings(const char *str, size_t len, size_t min);
void sanitize(void);
void show_around(zone_t *ptr, size_t range);

zone_t *find_zone(zone_t *ptr);

int compare(const void *first, const void *second);

#endif // DEBUG_H
