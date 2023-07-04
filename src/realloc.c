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

/* Increase size of chunk as much as possible by merging with unused blocks.
 * If sufficient, split and be done.
 * If not, allocate a new chunk, copy and free the old chunk
 */
void *_realloc(void *ptr, size_t size) {
	chunk_t *chunk = to_chunk(ptr);
	void	*ret   = NULL;

	merge(chunk);

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
