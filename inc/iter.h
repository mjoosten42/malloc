#ifndef ITER_H
#define ITER_H

#include "chunk.h"
#include "zone.h"

typedef struct iter {
	zone_t	*zone;
	chunk_t *chunk;
}	iter_t;

iter_t iter(zone_t *zones);
iter_t find(zone_t *zones);
chunk_t *next(iter_t *it);

void take(iter_t *it, size_t size);

int ok(iter_t *it);

#endif // ITER_H
