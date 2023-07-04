#include "chunk.h"
#include "impl.h"

#include <stdint.h> // uintptr_t
#include <stdlib.h> // abort

// TODO: remove
#include "debug.h"
#include "libft.h"

void free(void *ptr) {
	LOG("free(%p)\n", ptr);

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
	to_chunk(ptr)->used = 0;
}
