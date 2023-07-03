#include "iter.h"

#include "stdint.h" // uintptr_t
#include "zone.h"

iter_t find(zone_t *zones, size_t size) {
	zone_t	tmp	 = (zone_t){ .next = NULL };
	zone_t *prev = NULL;

	for (zone_t *zone = zones; zone; prev = zone, zone = zone->next) {
		chunk_t *chunk = begin(zone);
		int used = 0;

		if (zone->capacity - (ZONESIZE + 2 * CHUNKSIZE) < size) {
			continue;
		}

		for (; chunk != end(zone); chunk = next(chunk)) {
			if (!chunk->used) {
				merge(zone, chunk);
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
