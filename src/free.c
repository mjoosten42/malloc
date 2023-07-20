#include "chunk.h"
#include "debug.h" // LOG
#include "impl.h"

#include <signal.h> // TODO: remove
#include <stdint.h> // uintptr_t

export void free(void *ptr) {
	LOG("free(%p)\n", ptr);

	if (!ptr) {
		return;
	}

	pthread_mutex_lock(&mutex);
	_free(ptr);
	pthread_mutex_unlock(&mutex);
}

/* This does not merge chunks or unmap zones,
 * because finding the zone header from a chunk isn't possible.
 * Instead, cleanup is done at allocation time
 */
void _free(void *ptr) {
	chunk_t *chunk = ptr_to_chunk(ptr);

	chunk->used = 0;
}
