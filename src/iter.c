#include "iter.h"
#include "zone.h"
#include "stdint.h" // uintptr_t

#include "libft.h" // TODO: remove
#include "debug.h" // TODO: remove

iter_t iter(zone_t *zone) {
	chunk_t *chunk = NULL;

	if (zone) {
		chunk = chunks(zone);
	}

	return (iter_t){ zone, chunk };
}

iter_t 	find(zone_t *zones, fn f, void *arg) {
	for (zone_t *zone = zones; zone; zone = zone->next) {
		for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
			iter_t	it = { zone, chunk };

			if (f(&it, arg)) {
				return it;
			}
		}
	}

	return (iter_t){ NULL, NULL };
}

chunk_t *chunks(zone_t *zone) {
	return (chunk_t *)((uintptr_t)zone + ZONESIZE);
}

chunk_t *next(chunk_t *chunk) {
	return (chunk_t *)((uintptr_t)chunk + CHUNKSIZE + chunk->size);
}

chunk_t *to_chunk(void *ptr) {
	return (chunk_t *)((uintptr_t)ptr - CHUNKSIZE);
}

int ok(iter_t *iter) {
	return iter->zone != NULL;
}

