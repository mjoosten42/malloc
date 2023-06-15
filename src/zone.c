#include "malloc.h"		// PAGESIZE
#include "zone.h"
#include <sys/mman.h>	// mmap
#include <errno.h>		// errno
#include "iter.h"
#include "stdint.h" 	// uintptr_t

zone_t *new(size_t size) {
	size_t 	header_size = sizeof(zone_t) + 2 * sizeof(chunk_t);
	size_t 	capacity = align(size + header_size, PAGESIZE);
	zone_t 	*zone = allocate(capacity);

	if (!zone) {
		return NULL;
	}

	zone->next = NULL;
	zone->previous = NULL;
	zone->capacity = capacity;

	chunk_t *chunk = chunks(zone);

	*chunk = (chunk_t){ capacity - header_size, 0 };

	*next_chunk(chunk) = (chunk_t){ 0, 0 };

	return zone;
}

zone_t *append(zone_t **lst, zone_t *new) {
	zone_t *zone = *lst;

	if (!zone) {
		*lst = new;
	}

	while (zone) {
		if (!zone->next) {
			zone->next = new;
			break;
		}
		zone = zone->next;
	}

	return new;
}

void merge(zone_t *zone) {
	chunk_t *chunk = chunks(zone);
	chunk_t *prev = NULL;

	while (chunk->size) {
		if (prev && !prev->used && !chunk->used) {
			prev->size += sizeof(*chunk) + chunk->size;
		}

		prev = chunk;
		chunk = next_chunk(chunk);
	}
}

void 	*mem(chunk_t *chunk) {
	return (void *)((uintptr_t)chunk + sizeof(*chunk));
}

void 	take(chunk_t *chunk, size_t size) {
	size_t 	remaining = chunk->size - size;

	chunk->used = 1;
	chunk->size = size;

	if (remaining > sizeof(*chunk)) {
		*next_chunk(chunk) = (chunk_t){ remaining - sizeof(*chunk), 0 };
	} else {
		chunk->size += remaining;
	}
}

size_t align(size_t number, size_t alignment) {
	size_t minus_one = alignment - 1;

	return (number + minus_one) & ~minus_one;
}

void *allocate(size_t size) {
	int 	prot = PROT_READ | PROT_WRITE;
	int 	flags = MAP_ANONYMOUS | MAP_PRIVATE;
	void 	*ptr = mmap(NULL, size, prot, flags, -1, 0);
	
	// ft_printf("mmap: %p\n", ptr);

	if (ptr == MAP_FAILED) {
		ptr = NULL;
		perror("mmap"); // TODO: remove
		errno = ENOMEM;
	}

	return ptr;
}	

