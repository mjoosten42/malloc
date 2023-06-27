#include "chunk.h"

#include <stdint.h> // uintptr_t

chunk_t new(size_t size) {
	return (chunk_t){ size, 0 };
}

chunk_t *next(const chunk_t *chunk) {
	return (chunk_t *)((uintptr_t)chunk + CHUNKSIZE + chunk->size);
}

void split(chunk_t *chunk, size_t size) {
	size_t remaining = chunk->size - size;

	chunk->size = size;

	if (remaining > CHUNKSIZE) {
		*next(chunk) = new (remaining - CHUNKSIZE);
	} else {
		chunk->size += remaining;
	}
}

chunk_t *to_chunk(void *ptr) {
	return (chunk_t *)((uintptr_t)ptr - CHUNKSIZE);
}

void merge(chunk_t *chunk) {
	chunk_t *n = next(chunk);

	while (n->size && !n->used) {
		chunk->size += CHUNKSIZE + n->size;

		n = next(chunk);
	}
}

void *mem(const chunk_t *chunk) {
	return (void *)((uintptr_t)chunk + CHUNKSIZE);
}
