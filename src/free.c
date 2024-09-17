#include "chunk.h"
#include "debug.h" // LOG
#include "impl.h"
#include "zone.h"

#include <signal.h> // TODO: remove
#include <stdint.h> // uintptr_t

export void free(void *ptr) {
	LOG("free(%p)\n", ptr);

	if (!ptr) {
		return;
	}

	pthread_mutex_lock(&g_mutex);
	_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}

void _free(void *ptr) {
	chunk_t *chunk = ptr_to_chunk(ptr);
	zone_t *zone = find_zone(chunk);

	chunk->used = 0;

	#if MALLOC_SCRIBBLE
		ft_memset(chunk->memory, MALLOC_SCRIBBLE_VALUE, chunk->size);
	#endif

	clean(zone);
}
