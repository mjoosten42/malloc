#include "zone.h"

#include "memory.h" // align, PAGESIZE
#include <stdint.h> // uintptr_t

zone_t *map(size_t size) {
	size_t	capacity	= align(sizeof(zone_t) + size, PAGESIZE);
	zone_t *zone		= allocate(capacity);

	if (!zone) {
		return NULL;
	}

	zone->next	   = NULL;
	zone->prev	   = NULL;
	zone->capacity = capacity;
	zone->size	   = size;
	zone->free	   = zone->chunk;

	return zone;
}

void unmap(zone_t *zone) {
	if (zone->prev) {
		zone->prev->next = zone->next;
	}

	if (zone->next) {
		zone->next->prev = zone->prev;
	}

	deallocate(zone, zone->capacity);
}

// sorted
void push(zone_t **zones, zone_t *new) {
	zone_t *zone = *zones;

	if (!zone || zone > new) {
		*zones = new;

		new->next = zone;
		
		if (zone) {
			zone->prev = new;
		}
	
		return;
	}

	while (zone->next && zone < new) {
		zone = zone->next;
	}

	new->prev = zone;
	new->next = zone->next;

	if (zone->next) {
		zone->next->prev = new;
	}

	zone->next = new;
}

chunk_t *end(zone_t *zone) {
	return (chunk_t *)((uintptr_t)zone + zone->capacity);
}
