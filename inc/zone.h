#ifndef ZONE_H
#define ZONE_H

#include <stddef.h> // size_t, max_align_t

#define ZONESIZE	sizeof(zone_t)
#define CHUNKSIZE	sizeof(chunk_t)

/* [ ZONE  ]	sizeof(zone_t)
 * [ CHUNK ] 	sizeof(chunk_t)
 * [ ..... ]	chunk->size
 * [ CHUNK ]
 * [ ..... ]
 * etc...
 * [ CHUNK ]	chunk->size == 0
 */

/* Minimum zone (with PAGESIZE == 4096)
 * [ ZONE  ]	ZONESIZE
 * [ CHUNK ]	CHUNKSIZE
 * [ 4032  ]	(PAGESIZE - (ZONESIZE + 2 * CHUNKSIZE)
 * [ CHUNK ]	CHUNKSIZE
 */

struct zone {
	struct zone*	next;
	struct zone*	previous;
	size_t 			capacity;
	size_t			padding;
};

struct chunk {
	size_t 	size;
	int		used; // TODO: reduce size
};

typedef struct zone 	zone_t;
typedef struct chunk 	chunk_t;

zone_t 	*zone_new(size_t size);
void	zone_delete(zone_t *zone);
void	push(zone_t **lst, zone_t *new);

void 	split(chunk_t *chunk, size_t size);
void	clean(zone_t *zone);
void 	merge(zone_t *zone);
int		used(zone_t *zone);

void 	*mem(chunk_t *chunk);

#endif // ZONE_H
