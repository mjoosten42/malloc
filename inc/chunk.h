#ifndef CHUNK_H
#define CHUNK_H

#include "memory.h" // ALIGN

#include <stddef.h>

#define CHUNKSIZE align(sizeof(chunk_t), ALIGNMENT)

struct chunk {
	size_t		size;
	int			used;
	max_align_t memory[];
};

typedef struct chunk chunk_t;

chunk_t *next(const chunk_t *chunk);
chunk_t *ptr_to_chunk(void *ptr);
void	 split(chunk_t *chunk, size_t size);

#endif // CHUNK_H
