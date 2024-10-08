#include "debug.h"
#include "impl.h"
#include "libft.h"	// ft_memcpy
#include "memory.h" // align

/*	ptr		size
 *	*		0		_free
 *	0		!0		_malloc
 *  !0		!0		_realloc
 */

export void *realloc(void *ptr, size_t size) {
	void *ret = NULL;

	if (!size) {
		free(ptr);
		return NULL;
	}

	pthread_mutex_lock(&g_mutex);
	if (!ptr) {
		ret = _malloc(align(size, ALIGNMENT));
	} else {
		ret = _realloc(ptr, align(size, ALIGNMENT));
	}
	LOG("realloc(%p, %lu):\t%p\n", ptr, size, ret);
	pthread_mutex_unlock(&g_mutex);

	return ret;
}

/* Merge with next chunks if they're unused.
 * If size is sufficient, split and be done.
 * If not, allocate a new chunk, copy and free the old chunk
 */
void *_realloc(void *ptr, size_t size) {
	chunk_t *chunk	  = ptr_to_chunk(ptr);
	size_t	 old_size = chunk->size;
	void	 *ret	  = NULL;

	defragment(chunk);

	if (chunk->size >= size && table_get(old_size) == table_get(size)) {
		split(chunk, size);

		ret = chunk->memory;
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
