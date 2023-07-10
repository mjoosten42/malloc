#ifndef ZONE_H
#define ZONE_H

#include "chunk.h"
#include "memory.h" // ALIGN

#include <stddef.h> // size_t

#define ZONESIZE ALIGN(sizeof(zone_t), ALIGNMENT)

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
	struct zone *prev;
	size_t		 capacity;
};

typedef struct zone zone_t;

zone_t *map(size_t size);
void	unmap(zone_t *zone);
void	push(zone_t **lst, zone_t *new);
void	defragment(zone_t *zone);

int is_used(const zone_t *zone);

chunk_t *chunks(const zone_t *zone);
chunk_t *zone_end(const zone_t *zone);

zone_t *chunk_to_zone(const chunk_t *chunk);

size_t lst_size(zone_t *zones);

#endif // ZONE_H
