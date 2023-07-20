#include "debug.h"
#include "impl.h"	// mutex
#include "libft.h"	// ft_memcpy
#include "memory.h" // align

#include <pthread.h>

/*	ptr		size
 *	0		0		NULL
 *	0		!0		_malloc
 *	!0		0		_free
 *  !0		!0		_realloc
 */

export void *realloc(void *ptr, size_t size) {
	void *ret = NULL;

	if (!ptr && !size) {
		return NULL;
	}

	pthread_mutex_lock(&mutex);
	if (!ptr) {
		ret = _malloc(align(size, ALIGNMENT));
	} else if (!size) {
		_free(ptr);
	} else {
		ret = _realloc(ptr, align(size, ALIGNMENT));
	}
	LOG("realloc(%p, %lu):\t%p\n", ptr, size, ret);
	pthread_mutex_unlock(&mutex);

	return ret;
}

// This implementation doesn't work for realloc
void *_realloc(void *ptr, size_t size) {
	chunk_t *chunk = ptr_to_chunk(ptr);
	void *new = _malloc(size);

	if (!new) {
		return NULL;
	}

	ft_memcpy(new, ptr, MIN(chunk->size, size));

	_free(ptr);

	return new;
}
