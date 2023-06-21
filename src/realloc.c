#include "impl.h"
#include "libft.h"
#include "memory.h"	// align

// TODO: remove
#include <stdio.h>
#include "debug.h"

// TODO: error checking

void *realloc(void *ptr, size_t size) {
 	LOG("realloc: %p %d\n", ptr, size);

	void *ret = NULL;

	if (!ptr) {
		ret = _malloc(align(size, ALIGNMENT));
	} else {
		ret = _realloc(ptr, align(size, ALIGNMENT));
	}

	return ret;
}

void *_realloc(void *ptr, size_t size) {
	chunk_t *chunk = to_chunk(ptr);
	chunk_t *n = next(chunk);
	void	*ret = NULL;

	if (!n->used && chunk->size + CHUNKSIZE + n->size >= size) {
		chunk->size = size;

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
