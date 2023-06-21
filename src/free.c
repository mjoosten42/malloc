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

void	_free(void *ptr) {
	chunk_t *chunk = to_chunk(ptr); 

	chunk->used = 0;

	return ;
	// TODO: clean zone
	iter_t it = find(zones, is_ptr, &ptr);

	if (!ok(&it)) {
		abort();
	}

	clean(it.zone);
}

