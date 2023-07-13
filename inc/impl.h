#ifndef IMPL_H
#define IMPL_H

#include "zone.h" // zone_t

#include <pthread.h> // mutex
#include <stddef.h>	 // size_t

#define MIN(a, b) (a < b ? a : b)

// Maximum size to put in a small zone
#define LIMIT 4000UL

extern zone_t		  *zones;
extern pthread_mutex_t mutex;

void  _free(void *ptr);
void *_malloc(size_t size);
void *_realloc(void *ptr, size_t size);

chunk_t *find(zone_t *zone, size_t size);

#endif // IMPL_H
