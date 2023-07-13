#ifndef ZONE_H
#define ZONE_H

#include "chunk.h"
#include "memory.h" // ALIGN

#include <stddef.h> // size_t

#define ZONESIZE align(sizeof(zone_t), ALIGNMENT)
#define HEADERSIZE (ZONESIZE + 2 * CHUNKSIZE)

/* [ ZONE  ]	ZONESIZE
 * [ CHUNK ] 	CHUNKSIZE
 * [ ..... ]	chunk->size
 * [ CHUNK ]
 * [ ..... ]
 * etc...
 */

// mmap header
struct zone {
	struct zone *next;
	struct zone *prev;
	size_t		 capacity;
	chunk_t		 chunk[];
};

typedef struct zone zone_t;

zone_t *map(size_t size);
void	unmap(zone_t *zone);
void	push(zone_t **lst, zone_t *new);

void defragment(zone_t *zone);
int	 is_used(zone_t *zone);

zone_t *chunk_to_zone(chunk_t *chunk);

size_t lst_size(zone_t *zones);

#endif // ZONE_H
