#ifndef ZONE_H
#define ZONE_H

#include <stddef.h> // size_t, max_align_t
#include <unistd.h> // getpagesize

#define ALIGNMENT 	sizeof(void *) // TODO
#define PAGESIZE 	getpagesize()

/* [ ZONE ]		sizeof(zone_t)
 * [ ALLOC ] 	sizeof(chunk_t)
 * [ ... ]		chunk->size
 * [ ALLOC ]
 * [ ... ]
 * etc
 * [ ALLOC ]	chunk->size == 0
 */

struct chunk {
	size_t 	size;
	int 	used;
};

struct zone {
	struct zone*	next;
	struct zone*	previous;
	size_t 			capacity;
};

typedef struct chunk 	chunk_t;
typedef struct zone 	zone_t;

extern zone_t *zones;

zone_t 	*new(size_t size);
zone_t 	*append(zone_t **lst, zone_t *new);

void 	*mem(chunk_t *chunk);

void 	take(chunk_t *chunk, size_t size);
void 	merge(zone_t *zone);

#endif // ZONE_H
