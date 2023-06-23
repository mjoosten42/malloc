#include "zone.h"
#include "iter.h"
#include <stdlib.h> // abort
#include "impl.h"	// zones
#include <stdint.h>	// uintptr_t

// TODO: remove
#include "libft.h"
#include "debug.h"

void	free(void *ptr) {
	LOG("free(%p)\n", ptr);
	
	if (!ptr) {
		return ;
	}

	_free(ptr);
}

/* This does not merge chunks or unmap zones,
 * because finding the zone header from a chunk isn't possible.
 * Instead, cleanup is done at allocation time
 */
void	_free(void *ptr) {
	chunk_t *chunk = to_chunk(ptr); 

	chunk->used = 0;
}
