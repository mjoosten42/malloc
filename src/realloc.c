#include "debug.h"
#include "impl.h"
#include "libft.h"
#include "memory.h" // align

/*	ptr		size
 *	0		any		_malloc
 *	!0		0		_free
 *  !0		!0		_realloc
 */

void *realloc(void *ptr, size_t size) {
	void *ret = NULL;

	if (!ptr) {
		ret = _malloc(ALIGN(size, ALIGNMENT));
	} else if (!size) {
		_free(ptr);
	} else {
		ret = _realloc(ptr, ALIGN(size, ALIGNMENT));
	}

	LOCKED(LOG("realloc(%p, %lu):\t%p\n", ptr, size, ret));

	return ret;
}

/* Merge with next chunk if it's unused.
 * If size is sufficient, split and be done.
 * If not, allocate a new chunk, copy and free the old chunk
 */
void *_realloc(void *ptr, size_t size) {
	chunk_t *chunk = ptr_to_chunk(ptr);
	zone_t	*zone  = chunk_to_zone(chunk);
	chunk_t *n	   = next(chunk);
	void	*ret   = NULL;

	if (n != zone_end(zone) && !n->used) {
		chunk->size += CHUNKSIZE + n->size;
	}

	if (chunk->size >= size) {
		split(chunk, size);

		ret = mem(chunk);
	} else {
		void *new = _malloc(size);

		if (!new) {
			return NULL;
		}

		ft_memcpy(new, ptr, MIN(chunk->size, size));

		_free(ptr);

		ret = new;
	}

	return ret;
}
