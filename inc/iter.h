#ifndef ITER_H
#define ITER_H

#include "zone.h"

struct iter {
	struct zone	 *zone;
	struct chunk *chunk;
};

typedef struct iter iter_t;

iter_t find(zone_t *zone, size_t size);

int ok(iter_t *iter);

#endif // ITER_H
