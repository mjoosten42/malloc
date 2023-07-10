#include "chunk.h"
#include "debug.h" // LOG
#include "impl.h"

#include <stdint.h> // uintptr_t

void free(void *ptr) {
	LOCKED(LOG("free(%p)\n", ptr));

	if (!ptr) {
		return;
	}

	_free(ptr);
}

/* This does not merge chunks or unmap zones,
 * because finding the zone header from a chunk isn't possible.
 * Instead, cleanup is done at allocation time
 */
void _free(void *ptr) {
	chunk_t *chunk = ptr_to_chunk(ptr);
	zone_t	*zone  = chunk_to_zone(chunk);

	chunk->used = 0;

	defragment(zone);

	if (!is_used(zone)) {
		unmap(zone);
	}
}
