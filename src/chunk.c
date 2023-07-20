#include "chunk.h"
#include <stdint.h>

#include "zone.h"

chunk_t *ptr_to_chunk(void *ptr) {
	return (chunk_t *)((uintptr_t)ptr - sizeof(chunk_t));
}

chunk_t *next_chunk(zone_t *zone, chunk_t *chunk) {
	return (chunk_t *)((uintptr_t)chunk + sizeof(chunk_t) + zone->size);
}
