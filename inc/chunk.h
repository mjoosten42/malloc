#ifndef CHUNK_H
#define CHUNK_H

#include <stdalign.h>
#include <stddef.h>

typedef struct zone zone_t;

typedef struct chunk {
	size_t size;
	max_align_t	memory[];
}	chunk_t;

chunk_t *ptr_to_chunk(void *ptr);
chunk_t *next_chunk(zone_t *zone, chunk_t *chunk);

#endif // CHUNK_H
