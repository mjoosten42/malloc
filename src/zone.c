#include "zone.h"

#include "chunk.h"
#include "debug.h"
#include "impl.h"	// zones
#include "memory.h" // align, PAGESIZE

#include <stdint.h> // uintptr_t

zone_t *map(size_t size) {
	size_t	capacity = align(size + HEADERSIZE, PAGESIZE);
	zone_t *zone	 = allocate(capacity);

	if (!zone) {
		return NULL;
	}

	zone->next	   = NULL;
	zone->prev	   = NULL;
	zone->capacity = capacity;

	*zone->chunk = (chunk_t){ capacity - HEADERSIZE, 0 };

	// close with zero-size chunk
	*next(zone->chunk) = (chunk_t){ 0, 1 };

	return zone;
}

void unmap(zone_t *zone) {
	if (!zone->capacity) {
		LOG("%s:%d\n", __FILE__, __LINE__);
		abort();
	}

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
	zone_t *head = *zones;

	new->next = head;

	if (head) {
		head->prev = new;
	}

	*zones = new;
}

void defragment(zone_t *zone) {
	for (chunk_t *chunk = zone->chunk; chunk->size; chunk = next(chunk)) {
		if (!chunk->used) {
			for (chunk_t *n = next(chunk); n->size && !n->used; n = next(n)) {
				chunk->size += CHUNKSIZE + n->size;
			}
		}
	}
}

int is_used(zone_t *zone) {
	for (chunk_t *chunk = zone->chunk; chunk->size; chunk = next(chunk)) {
		if (chunk->used) {
			return 1;
		}
	}

	return 0;
}

chunk_t *zone_end(zone_t *zone) {
	return (chunk_t *)((uintptr_t)zone + zone->capacity);
}

// Zero out the last few bits
// This works because no chunks are allowed to start past PAGESIZE of a zone
zone_t *chunk_to_zone(chunk_t *chunk) {
	return (zone_t *)((uintptr_t)chunk & ~(PAGESIZE - 1));
}

size_t lst_size(zone_t *zones) {
	size_t count = 0;

	for (zone_t *zone = zones; zone; zone = zone->next) {
		count++;
	}

	return count;
}
