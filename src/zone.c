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
	zone->prev	= NULL;
	zone->capacity = capacity;

	chunk_t *chunk = chunks(zone);

	*chunk = (chunk_t){ capacity - header_size, 0 };

	*next(chunk) = (chunk_t){ 0, 0 };

	return zone;
}

void unmap(zone_t *zone) {
	if (zone->prev) {
		zone->prev->next = zone->next;
	}

	if (zone->next) {
		zone->next->prev = zone->prev;
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

void	defragment(zone_t *zone) {
	for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
		for (chunk_t *n = chunk; n->size && !n->used; n = next(n)) {
			chunk->size += CHUNKSIZE + n->size;
		}
	}
}

int		is_used(const zone_t *zone) {
	for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
		if (chunk->used) {
			return 1;
		}
	}

	return 0;
}

chunk_t *chunks(const zone_t *zone) {
	return (chunk_t *)((uintptr_t)zone + ZONESIZE);
}

zone_t	*chunk_to_zone(const chunk_t *chunk) {
	zone_t *zone = NULL;

	if (chunk->size > LIMIT) {
		// Assume this is the first chunk
		zone = (zone_t *)((uintptr_t)chunk - ZONESIZE);
	} else {
		// Assume zone contains only one page
		zone = (zone_t *)((uintptr_t)chunk & ~(PAGESIZE - 1));
	}

	return zone;
}

size_t lst_size(zone_t *zones) {
	size_t count = 0;

	for (zone_t *zone = zones; zone; zone = zone->next) {
		count++;
	}

	return count;
}
