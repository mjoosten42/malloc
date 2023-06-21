#include "zone.h"
#include "iter.h"
#include <stdint.h> // uintptr_t
#include "memory.h" // align, PAGESIZE
#include "impl.h"	// zones

zone_t	*zone_new(size_t size) {
	size_t 	header_size = sizeof(zone_t) + 2 * sizeof(chunk_t);
	size_t 	capacity = align(size + header_size, PAGESIZE);
	zone_t 	*zone = allocate(capacity);

	if (!zone) {
		return NULL;
	}

	zone->next = NULL;
	zone->previous = NULL;
	zone->capacity = capacity;

	chunk_t *chunk = chunks(zone);

	*chunk = (chunk_t){ capacity - header_size, 0 };

	*next(chunk) = (chunk_t){ 0, 0 };

	return zone;
}

void	zone_delete(zone_t *zone) {
	if (zone->next) {
		zone->next->previous = zone->previous;
	}

	if (zone->previous) {
		zone->previous->next = zone->next;
	}

	if (zone == zones) {
		zones = zone->next;
	}
}

void	push(zone_t **lst, zone_t *new) {
	new->next = *lst;

	*lst = new;
}

void 	take(chunk_t *chunk, size_t size) {
	size_t 	remaining = chunk->size - size;

	chunk->used = 1;
	chunk->size = size;

	if (remaining > sizeof(*chunk)) {
		*next(chunk) = (chunk_t){ remaining - sizeof(*chunk), 0 };
	} else {
		chunk->size += remaining;
	}
}

void	clean(zone_t *zone) {
	merge(zone);

	if (!used(zone)) {
		zone_delete(zone);
	}
}

#include "libft.h"
void	merge(zone_t *zone) {
	chunk_t *prev = NULL;

	for (chunk_t *chunk = chunks(zone); chunk->size; next(chunk)) {
		if (prev && !prev->used && !chunk->used) {
			prev->size += sizeof(*chunk) + chunk->size;
		}

		prev = chunk;
	}
}

int		used(zone_t *zone) {
	for (chunk_t *chunk = chunks(zone); chunk->size; next(chunk)) {
		if (chunk->used) {
			return 1;
		}			
	}

	return 0;

}

void 	*mem(chunk_t *chunk) {
	return (void *)((uintptr_t)chunk + sizeof(*chunk));
}

