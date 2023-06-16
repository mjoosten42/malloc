#include "impl.h"
#include "iter.h"	// iter_t
#include "memory.h"	// align, ALIGNMENT

#include <stdio.h>	// TODO: remove

static int	with_space(iter_t *it, void *arg);

zone_t	*zones = NULL;

void	*_malloc(size_t size) {
	iter_t it = find(zones, with_space, &size);

	if (!ok(&it)) {
		zone_t *zone = zone_new(size);

		if (!zone) {
			return NULL;
		}
	
		push(&zones, zone);

		it = find(zone, with_space, &size);
	}

	take(it.chunk, size);

 	return mem(it.chunk);
}

static int with_space(iter_t *it, void *arg) {
	size_t 	size = *(size_t *)arg;
	chunk_t *chunk = it->chunk;

	return !chunk->used && chunk->size >= size;
}

