#include "impl.h"
#include "libft.h"
#include "memory.h" // align

// TODO: remove
#include "debug.h"

#include <stdio.h>

/*	ptr		size
 *	0		any		_malloc
 *	> 0		0		_free + NULL
 *  > 0		> 0		_realloc
 */

void *realloc(void *ptr, size_t size) {
	LOG("realloc: %p %d\n", ptr, size);

	void *ret = NULL;

	if (!ptr) {
		ret = _malloc(ALIGN(size, ALIGNMENT));
	} else if (!size) {
		_free(ptr);
	} else {
		ret = _realloc(ptr, ALIGN(size, ALIGNMENT));
	}

	return ret;
}

/* Increase size of chunk as much as possible.
 * If sufficient, split and be done.
 * If not, reset size, allocate a new chunk, copy and free the old chunk
 */
void *_realloc(void *ptr, size_t size) {
	chunk_t *chunk	  = to_chunk(ptr);
	size_t	 old_size = chunk->size;
	void	*ret	  = NULL;

	merge(chunk);

	if (chunk->size >= size) {
		split(chunk, size);

		ret = mem(chunk);
	} else {
		split(chunk, old_size);

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
