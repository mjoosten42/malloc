#ifndef CHUNK_H
#define CHUNK_H

#include <stddef.h>

#define CHUNKSIZE sizeof(chunk_t)

struct chunk {
	size_t size;
	int	   used;
};

typedef struct chunk chunk_t;

chunk_t new(size_t size);
chunk_t *next(const chunk_t *chunk);
chunk_t *to_chunk(void *ptr);
void	 split(chunk_t *chunk, size_t size);
void	*mem(const chunk_t *chunk);

#endif // CHUNK_H
