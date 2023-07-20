#include "chunk.h"
#include "debug.h" // LOG
#include "impl.h"  // mutex
#include "table.h" // get

#include <pthread.h>

export void free(void *ptr) {
	LOG("free(%p)\n", ptr);

	if (!ptr) {
		return;
	}

	pthread_mutex_lock(&mutex);
	_free(ptr);
	pthread_mutex_unlock(&mutex);
}

void _free(void *ptr) {
	chunk_t *chunk = ptr_to_chunk(ptr);
	// zone_t *zone = get(&table, align(chunk->size));

	chunk->size = 0;

}
