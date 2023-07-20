#ifndef ZONE_H
#define ZONE_H

#include "chunk.h"

#include <stddef.h> // size_t

/* [ ZONE  ]
 * [ CHUNK ] 	CHUNKSIZE
 * [ ..... ]	chunk->size
 * etc...
 * [ CHUNK ]	zero size
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

size_t	 lst_size(zone_t *zones);
zone_t **zone_list(zone_t *zones);

#endif // ZONE_H
