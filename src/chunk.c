#include "chunk.h"

#include <stdint.h> // uintptr_t

chunk_t *next(const chunk_t *chunk) {
	return (chunk_t *)((uintptr_t)chunk + CHUNKSIZE + chunk->size);
}

void split(chunk_t *chunk, size_t size) {
	size_t remaining = chunk->size - size;

	if (remaining > CHUNKSIZE) {
		chunk->size = size;

		*next(chunk) = (chunk_t){ remaining - CHUNKSIZE, 0 };
	}
}

chunk_t *ptr_to_chunk(void *ptr) {
	return (chunk_t *)((uintptr_t)ptr - CHUNKSIZE);
}
