#include "debug.h" // TODO
#include "impl.h"  // _malloc
#include "libft.h"
#include "memory.h" // ALIGN, ALIGNMENT

zone_t *zones = NULL;

void *malloc(size_t size) {
	if (!size) {
		return NULL;
	}

	void *ret = _malloc(ALIGN(size, ALIGNMENT));

#ifdef MallocPreScribble
	if (ret) {
		ft_memset(ptr, PRESCRIBBLE, to_chunk(ptr)->size);
	}
#endif

	LOG("malloc(%d):", size);
	LOG("\t\t%p\n", ret);

	LOCKED(save_log(ret, size));

	return ret;
}

void *_malloc(size_t size) {
	iter_t	 it	   = find(zones, size);
	chunk_t *chunk = it.chunk;

	if (!ok(&it)) {
		zone_t *zone = map(size);

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
