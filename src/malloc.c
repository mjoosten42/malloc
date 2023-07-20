#include "debug.h"
#include "impl.h"	// _malloc
#include "memory.h" // ALIGN, ALIGNMENT

#include <errno.h>
#include <pthread.h>
#include <stdio.h>

zone_t		   *zones = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

export void *malloc(size_t size) {
	if (!size) {
		return NULL;
	}

	pthread_mutex_lock(&mutex);
	void *ret = _malloc(align(size, ALIGNMENT));
	LOG("malloc(%lu):\t\t\t%p\n", size, ret);
	pthread_mutex_unlock(&mutex);

	return ret;
}

void *_malloc(size_t size) {
	chunk_t *chunk = find(zones, size);

	if (!chunk) {
		zone_t *zone = map(size);

		if (!zone) {
			return NULL;
		}

		push(&zones, zone);

		chunk = zone->chunk;
	}

	split(chunk, size);

	chunk->used = 1;

	return chunk->memory;
}

chunk_t *find(zone_t *zones, size_t size) {
	zone_t tmp;
	
	for (zone_t *zone = zones; zone; zone = zone->next) {
		defragment(zone);

		for (chunk_t *chunk = zone->chunk; chunk->size; chunk = next(chunk)) {
			if (!chunk->used && chunk->size >= size) {
				return chunk;
			}
		}

		if (!is_used(zone)) {
			tmp = *zone;

			unmap(zone);

			zone = &tmp;
		}
	}

	return NULL;
}
