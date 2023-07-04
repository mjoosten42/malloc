#include "zone.h"

#include "chunk.h"
#include "debug.h"
#include "impl.h"	// zones
#include "memory.h" // ALIGN, PAGESIZE

#include <stdint.h> // uintptr_t

zone_t *map(size_t size) {
	size_t	header_size = ZONESIZE + 2 * CHUNKSIZE;
	size_t	capacity	= ALIGN(size + header_size, PAGESIZE);
	zone_t *zone		= allocate(capacity);

	if (!zone) {
		return NULL;
	}

	zone->next	   = NULL;
	zone->capacity = capacity;

	chunk_t *chunk = chunks(zone);

	*chunk = (chunk_t){ capacity - header_size, 0 };

	*next(chunk) = (chunk_t){ 0, 0 };

	return zone;
}

void unmap(zone_t *zone, zone_t *prev) {
	if (prev) {
		prev->next = zone->next;
	}

	if (zone == zones) {
		zones = zone->next;
	}

	deallocate(zone, zone->capacity);
}

void push(zone_t **zones, zone_t *new) {
	new->next = *zones;

	*zones = new;
}

chunk_t *chunks(const zone_t *zone) {
	return (chunk_t *)((uintptr_t)zone + ZONESIZE);
}

void merge(chunk_t *chunk) {
	for (chunk_t *n = next(chunk); n->size; n = next(chunk)) {
		chunk->size += CHUNKSIZE + n->size;
	}
}
