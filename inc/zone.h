#ifndef ZONE_H
#define ZONE_H

#include <stddef.h> // size_t, max_align_t

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

zone_t 	*zone_new(size_t size);
void	zone_delete(zone_t *zone);
void	push(zone_t **lst, zone_t *new);

void 	take(chunk_t *chunk, size_t size);
void	clean(zone_t *zone);
void 	merge(zone_t *zone);
int		used(zone_t *zone);

void 	*mem(chunk_t *chunk);

#endif // ZONE_H
