#ifndef CHUNK_H
#define CHUNK_H

#include <stdalign.h>
#include <stddef.h>

#define CHUNKSIZE sizeof(chunk_t)

struct chunk {
	size_t		size;
	int			used;
	max_align_t memory[];
};

typedef struct chunk chunk_t;

chunk_t *next(const chunk_t *chunk);
chunk_t *ptr_to_chunk(void *ptr);
void	 split(chunk_t *chunk, size_t size);
void 	 defragment(chunk_t *chunk);

#endif // CHUNK_H
