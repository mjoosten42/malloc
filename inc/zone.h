#ifndef ZONE_H
#define ZONE_H

#include "chunk.h"

#include <stddef.h> // size_t

typedef struct zone {
	struct zone *next;
	struct zone *prev;

	size_t		 capacity; // bytes mmap'ed
	size_t		 size; // size of chunks

	chunk_t		*free; // first free chunk

	chunk_t		 chunk[];
}	zone_t;

zone_t *map(size_t size);
void	unmap(zone_t *zone);
void	push(zone_t **zones, zone_t *zone);

chunk_t *end(zone_t *zone);

#endif // ZONE_H
