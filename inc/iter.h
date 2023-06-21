#ifndef ITER_H
#define ITER_H

#include "zone.h"

struct iter {
	struct zone* 	zone;
	struct chunk* 	chunk;
};

typedef struct iter iter_t;

typedef int (*fn)(iter_t *iter, void *arg);

iter_t 	iter(zone_t *zone);
iter_t 	find(zone_t *zone, fn f, void *arg);

chunk_t *chunks(zone_t *zone);
chunk_t *next(chunk_t *chunk);
chunk_t *to_chunk(void *ptr);

int 	ok(iter_t *iter);

#endif // ITER_H
