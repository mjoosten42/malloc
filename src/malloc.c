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
	int 	is_small = size <= LIMIT;
	
	iter_t	 it	   = (iter_t){ NULL, NULL };
	chunk_t *chunk = NULL;

	if (is_small) {
		it = find(zones, size);
		chunk = it.chunk;
	}

	if (!ok(&it)) {
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
