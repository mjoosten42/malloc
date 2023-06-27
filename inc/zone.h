#ifndef ZONE_H
#define ZONE_H

#include "chunk.h"

#include <stddef.h> // size_t

#define ZONESIZE sizeof(zone_t)

/* [ ZONE  ]	sizeof(zone_t)
 * [ CHUNK ] 	sizeof(chunk_t)
 * [ ..... ]	chunk->size
 * [ CHUNK ]
 * [ ..... ]
 * etc...
 * [ CHUNK ]	chunk->size == 0
 *
 * Minimum zone (with PAGESIZE == 4096)
 * [ ZONE  ]	ZONESIZE
 * [ CHUNK ]	CHUNKSIZE, chunk->size == 4032
 * [ 4032  ]	(PAGESIZE - (ZONESIZE + 2 * CHUNKSIZE)
 * [ CHUNK ]	CHUNKSIZE, chunk->size == 0
 */

// mmap header
struct zone {
	struct zone *next;
	size_t		 capacity;
};

typedef struct zone zone_t;

zone_t *map(size_t size);
void	unmap(zone_t *zone, zone_t *prev);

void push(zone_t **lst, zone_t *new);

chunk_t *chunks(zone_t *zone);

#endif // ZONE_H
