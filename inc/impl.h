#ifndef IMPL_H
#define IMPL_H

#include "iter.h" // iter_t
#include "zone.h" // zone_t

#include <pthread.h> // pthread_mutex_t
#include <stddef.h>	 // size_t

#define MIN(a, b) (a < b ? a : b)

// Maximum size to put in a small zone
#define LIMIT 4000UL

extern zone_t *zones;

void  _free(void *ptr);
void *_malloc(size_t size);
void *_realloc(void *ptr, size_t size);

#endif // IMPL_H
