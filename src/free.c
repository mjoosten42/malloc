#include "chunk.h"
#include "debug.h" // TODO
#include "impl.h"
#include "libft.h"

void free(void *ptr) {
	LOG("free(%p)\n", ptr);

	if (!ptr) {
		return;
	}

	_free(ptr);

	get_log(ptr)->freed = 1;
}

/* This does not merge chunks or unmap zones,
 * because finding the zone header from a chunk isn't possible.
 * Instead, cleanup is done at allocation time
 */
void _free(void *ptr) {
	chunk_t *chunk = to_chunk(ptr);

	chunk->used = 0;

#ifdef MallocScribble
	ft_memset(ptr, SCRIBBLE, chunk->size);
#endif
}
