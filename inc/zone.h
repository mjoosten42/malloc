#ifndef ZONE_H
#define ZONE_H

#include <stddef.h> // size_t
#include <unistd.h> // getpagesize

#define ALIGNMENT 	sizeof(void *)
#define PAGESIZE getpagesize()

/* [ ZONE ]		sizeof(zone_t)
 * [ ALLOC ] 	sizeof(alloc_t)
 * [ ... ]		alloc->size
 * [ ALLOC ]
 * [ ... ]
 * etc
 * [ ALLOC ]	alloc->size == 0
 */

struct alloc {
	size_t 	size;
	int 	used;
};

struct zone {
	struct zone*	next;
	struct zone*	previous;
};

typedef struct alloc 	alloc_t;
typedef struct zone 	zone_t;

extern zone_t *zones;

zone_t 	*new(size_t size);
zone_t 	*append(zone_t **lst, zone_t *new);
void 	merge(zone_t *zone);

alloc_t *chunks(zone_t *zone);
alloc_t *next(alloc_t *alloc);
alloc_t *find(zone_t **zones, size_t size);
void 	*mem(alloc_t *alloc);
void 	take(alloc_t *alloc, size_t size);

size_t 	align(size_t size, size_t alignment);
void 	*allocate(size_t size);

#endif // ZONE_H
