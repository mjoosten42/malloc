#include "impl.h"
#include "iter.h"	// iter_t
#include "memory.h"	// align, ALIGNMENT

#include <stdio.h>	// TODO: remove

zone_t	*zones = NULL;

void	*_malloc(size_t size) {
	iter_t it = find(zones, with_space, &size);

	if (!ok(&it)) {
		zone_t *zone = zone_new(size);

		if (!zone) {
			return NULL;
		}
	
		push(&zones, zone);

		it.chunk = chunks(zone);
	}

	chunk_t *chunk = it.chunk;

	split(chunk, size);
	
	chunk->used = 1;

 	return mem(chunk);
}

int with_space(iter_t *it, void *arg) {
	size_t 	size = *(size_t *)arg;
	chunk_t *chunk = it->chunk;

	return !chunk->used && chunk->size >= size;
}

int is_ptr(iter_t *it, void *arg) {
	return mem(it->chunk) == *(void **)arg;
}

