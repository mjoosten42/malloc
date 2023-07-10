#include "debug.h"
#include "impl.h"	// _malloc
#include "memory.h" // ALIGN, ALIGNMENT

#include <stdio.h>

zone_t *zones = NULL;

void *malloc(size_t size) {
	if (!size) {
		return NULL;
	}

	void *ret = _malloc(ALIGN(size, ALIGNMENT));

	LOCKED(LOG("malloc(%lu):\t\t%p\n", size, ret));

	return ret;
}

void *_malloc(size_t size) {
	chunk_t *chunk	  = NULL;
	int		 is_small = size <= LIMIT;

	if (is_small) {
		chunk = find(zones, size);
	}

	if (!chunk) {
		zone_t *zone = map(size);

		if (!zone) {
			return NULL;
		}

		push(&zones, zone);

		chunk = chunks(zone);
	}

	if (is_small) {
		split(chunk, size);
	}

	chunk->used = 1;

	return mem(chunk);
}

chunk_t *find(zone_t *zones, size_t size) {
	for (zone_t *zone = zones; zone; zone = zone->next) {
		chunk_t *end = zone_end(zone);

		if (zone->capacity > LIMIT) {
			continue;
		}

		for (chunk_t *chunk = chunks(zone); chunk != end; chunk = next(chunk)) {
			if (!chunk->used && chunk->size >= size) {
				return chunk;
			}
		}
	}

	return NULL;
}

