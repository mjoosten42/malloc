#ifndef ITER_H
#define ITER_H

#include "zone.h"

struct iter {
	struct zone* 	zone;
	struct chunk* 	chunk;
};

typedef struct iter iter_t;

typedef int (*fun)(iter_t *iter, void *arg);

iter_t 	iter(zone_t **zones);
iter_t 	*_next(iter_t *iter);
iter_t 	find(zone_t **zones, fun f, void *arg);

chunk_t *chunks(zone_t *zone);
chunk_t *next_chunk(chunk_t *chunk);

int 	ok(iter_t *iter);

#endif // ITER_H
