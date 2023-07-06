#ifndef CHUNK_H
#define CHUNK_H

#include "memory.h" // ALIGN

#include <stddef.h>

#define CHUNKSIZE ALIGN(sizeof(chunk_t), ALIGNMENT)

struct chunk {
	size_t size;
	int	   used;
};

typedef struct chunk chunk_t;

chunk_t *next(const chunk_t *chunk);
chunk_t *ptr_to_chunk(void *ptr);
void	 split(chunk_t *chunk, size_t size);
void	*mem(const chunk_t *chunk);

#endif // CHUNK_H
