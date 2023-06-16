#ifndef IMPL_H
#define IMPL_H

#include <stddef.h>	// size_t
#include "zone.h"	// zone_t
#include "iter.h"	// iter_t

extern zone_t *zones;

void	_free(void *ptr);
void	*_malloc(size_t size);
void	*_realloc(void *ptr, size_t size);

void	print();

#endif // IMPL_H
