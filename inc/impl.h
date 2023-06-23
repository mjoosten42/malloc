#ifndef IMPL_H
#define IMPL_H

#include <stddef.h>	// size_t
#include "zone.h"	// zone_t
#include "iter.h"	// iter_t

#define MIN(a, b) (a < b ? a : b)

extern zone_t *zones;

void	_free(void *ptr);
void	*_malloc(size_t size);
void	*_realloc(void *ptr, size_t size);

#endif // IMPL_H
