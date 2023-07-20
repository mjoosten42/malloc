#include "zone.h"

#include "chunk.h"
#include "impl.h"	// zones
#include "memory.h" // align, PAGESIZE

#include <stdint.h> // uintptr_t
#include <stdlib.h> // qsort

zone_t *map(size_t size) {
	size_t	header_size = sizeof(zone_t) + 2 * CHUNKSIZE;
	size_t	capacity	= align(size + header_size, PAGESIZE);
	zone_t *zone		= allocate(capacity);

	if (!zone) {
		return NULL;
	}

	zone->next	   = NULL;
	zone->prev	   = NULL;
	zone->capacity = capacity;

	*zone->chunk = (chunk_t){ capacity - header_size, 0 };

	// close with zero-size chunk
	*next(zone->chunk) = (chunk_t){ 0, 1 };

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

size_t lst_size(zone_t *zones) {
	size_t count = 0;

	for (zone_t *zone = zones; zone; zone = zone->next) {
		count++;
	}

	return count;
}

static int compare(const void *first, const void *second) {
	return *(zone_t **)first < *(zone_t **)second;
}

// returns a sorted, malloc'ed array of zone pointers
zone_t **zone_list(zone_t *zones) {
	size_t	 size  = lst_size(zones);
	zone_t **array = _malloc(align(sizeof(zone_t *) * (size + 1), ALIGNMENT));
	size_t	 i	   = 0;

	if (!array) {
		return NULL;
	}

	for (zone_t *zone = zones; zone; zone = zone->next) {
		array[i++] = zone;
	}

	qsort((void *)array, size, sizeof(zone_t *), compare);

	array[size] = NULL;

	return array;
}
