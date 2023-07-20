#include "debug.h"
#include "impl.h"	// _malloc
#include "memory.h" // ALIGN, ALIGNMENT
#include "table.h"	// table_t
#include "iter.h"

#include <errno.h>
#include <pthread.h>
#include <stdio.h>

zone_t		   *zones = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
table_t			table = { NULL, 0, 0 };

export void *malloc(size_t size) {
	if (!size) {
		return NULL;
	}

	pthread_mutex_lock(&mutex);
	void *ret = _malloc(size);
	LOG("malloc(%lu):\t\t\t%p\n", size, ret);
	pthread_mutex_unlock(&mutex);

	return ret;
}

void *_malloc(size_t size) {
	size_t aligned = align(size, ALIGNMENT);
	zone_t *zone = get(&table, aligned);

	if (!zone) {
		return NULL;
	}

	iter_t it = find(zone);

	if (!ok(&it)) {
		zone_t *new = map(aligned);

		if (!new) {
			return NULL;
		}

		push(&zone, new);

		zone = new;
	}

	take(&it, size);

	return it.chunk->memory;
}
