#include "impl.h"	// _malloc
#include "memory.h"	// ALIGN, ALIGNMENT

// TODO: remove
#include "debug.h"	
#include "libft.h"
#include <stdio.h>

zone_t	*zones = NULL;

void	*malloc(size_t size) {
	if (!size) {
		return NULL;
	}

	void *ret = _malloc(ALIGN(size, ALIGNMENT));
		
	LOG("malloc(%d):", size);
	LOG("\t\t%p\n", ret);

	return ret;
}

void	*_malloc(size_t size) {
	iter_t	it = find(zones, size);
	zone_t	*zone = it.zone;
	chunk_t	*chunk = it.chunk;

	if (!ok(&it)) {
		zone = map(size);

		if (!zone) {
			return NULL;
		}

		push(&zones, zone);

		chunk = chunks(zone);
	}

	split(chunk, size);
	
	chunk->used = 1;

 	return mem(chunk);
}

