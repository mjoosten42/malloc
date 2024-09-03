#include "debug.h"
#include "impl.h"	// _malloc
#include "memory.h" // ALIGN, ALIGNMENT

#include <errno.h>
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
table_t 		g_table = { NULL, NULL, NULL };

export void *malloc(size_t size) {
	if (!size) {
		return NULL;
	}

	pthread_mutex_lock(&g_mutex);
	void *ret = _malloc(align(size, ALIGNMENT));
	LOG("malloc(%lu):\t\t\t%p\n", size, ret);
	pthread_mutex_unlock(&g_mutex);

	return ret;
}

void *_malloc(size_t size) {
	zone_t *root = table_get(size);

	if (!root) {
		return NULL;
	}

	chunk_t *chunk = find(root, size);

	if (!chunk) {
		zone_t *zone = map(size);

		if (!zone) {
			return NULL;
		}

		push_back(root, zone);

		chunk = zone->chunk;
	}

	split(chunk, size);

	chunk->used = 1;

	return chunk->memory;
}

chunk_t *find(zone_t *zones, size_t size) {
	for (zone_t *zone = zones; zone; zone = zone->next) {
		for (chunk_t *chunk = zone->chunk; chunk->size; chunk = next(chunk)) {
			if (!chunk->used && chunk->size >= size) {
				return chunk;
			}
		}
	}

	return NULL;
}
