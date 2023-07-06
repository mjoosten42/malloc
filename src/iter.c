#include "iter.h"

#include "stdint.h" // uintptr_t
#include "zone.h"
#include "impl.h" // LIMIT

iter_t find(zone_t *zones, size_t size) {
	for (zone_t *zone = zones; zone; zone = zone->next) {

		// TODO: skip LARGE zones	
		// if (zone->capacity > LIMIT) {
		// 	continue;
		// }

		for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
			if (!chunk->used && chunk->size >= size) {
				return (iter_t){ zone, chunk };
			}
		}

	}

	return (iter_t){ NULL, NULL };
}

int ok(iter_t *iter) {
	return iter->zone != NULL;
}
