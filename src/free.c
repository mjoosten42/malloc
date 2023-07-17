#include "chunk.h"
#include "debug.h" // LOG
#include "impl.h"

#include <signal.h> // TODO: remove
#include <stdint.h> // uintptr_t

void free(void *ptr) {
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
	zone_t	*zone  = chunk_to_zone(chunk);

	if (!zone->capacity || zone->capacity % PAGESIZE) {
		zone_t *prev = find_zone(zone);

		show_around(zone, 64);
		ft_printf("zone: %p %lu\n", zone, zone->capacity);
		ft_printf("prev: %p\n", prev);
		raise(SIGTRAP);
		abort();
		(void)prev;
	}

	chunk->used = 0;

	defragment(zone);

	if (!is_used(zone)) {
		unmap(zone);
	}
}
