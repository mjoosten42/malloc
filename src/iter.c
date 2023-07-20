#include "iter.h"
#include "chunk.h"
#include <stdint.h>

iter_t iter(zone_t *zone) {
	return (iter_t){ zone, zone->chunk };
}

iter_t find(zone_t *zones) {
	iter_t it = iter(zones);

	for (chunk_t *chunk = it.chunk; chunk; chunk = next(&it)) {
		if (!chunk->size) {
			break ;
		}	
	}

	return it;
	
}

chunk_t *next(iter_t *it) {
	chunk_t *next = next_chunk(it->zone, it->chunk);
	
	if (next >= end(it->zone)) {
		it->zone = it->zone->next;

		if (!it->zone) {
			return NULL	;
		}

		it->chunk = it->zone->chunk;
	} else {
		it->chunk = next;
	}

	return it->chunk;
}

void take(iter_t *it, size_t size) {
	it->chunk->size = size; 
}

int ok(iter_t *it) {
	return it->zone != NULL;
}
