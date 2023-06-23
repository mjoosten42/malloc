#include "iter.h"
#include "zone.h"
#include "stdint.h" // uintptr_t

iter_t 	find(zone_t *zones, size_t size) {
	zone_t tmp = (zone_t){ .next = NULL, .capacity = 42 };
	zone_t *prev = NULL;

	for (zone_t *zone = zones; zone; zone = zone->next, prev = zone) {
		int	used = 0;

		for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
			if (!chunk->used) {
				merge(chunk);
			}

			if (!chunk->used && chunk->size >= size) {
				return (iter_t){ zone, chunk };
			}

			if (chunk->used) {
				used = 1;
			}
		}

		if (!used) {
			tmp = *zone;

			// After munmap, reading from zone would segfault
			unmap(zone, prev);

			zone = &tmp;
		}
	}

	return (iter_t){ NULL, NULL };
}

int ok(iter_t *iter) {
	return iter->zone != NULL;
}

