#include "malloc.h"		// PAGESIZE
#include "zone.h"
#include <sys/mman.h>	// mmap
#include <errno.h>		// errno

zone_t *new(size_t size) {
	size_t 	header_size = sizeof(zone_t) + 2 * sizeof(chunk_t);
	size_t 	capacity = align(size + header_size, PAGESIZE);
	zone_t 	*zone = allocate(capacity);

	if (!zone) {
		return NULL;
	}

	zone->next = NULL;
	zone->previous = NULL;

	chunk_t *chunk = chunks(zone);

	*chunk = (chunk_t){ capacity - header_size, 0 };

	*next(chunk) = (chunk_t){ 0, 0 };

	return zone;
}

chunk_t *find(zone_t **zones, size_t size) {
	for (zone_t *zone = *zones; zone != NULL; zone = zone->next) {
		for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
			if (!chunk->used && chunk->size >= sizeof(*chunk) + size) {
				return chunk;
			}	
		}
	}

	return NULL;
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
	for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
		if (!chunk->used) {
			for (chunk_t *n = next(chunk); n->size && !n->used; n = next(n)) {
				chunk->size += n->size + sizeof(*chunk);
			}
		}
	}
}

chunk_t *chunks(zone_t *zone) {
	return (chunk_t *)((size_t)zone + sizeof(*zone));
}

chunk_t *next(chunk_t *chunk) {
	chunk_t *ret = (chunk_t *)((size_t)chunk + sizeof(*chunk) + chunk->size);

	// TODO: remove
	if (ret == chunk) {
		ft_printf("next: infinite loop\n");
		exit(1);
	}

	return ret;
}

void 	*mem(chunk_t *chunk) {
	return (void *)((size_t)chunk + sizeof(*chunk));
}

void 	take(chunk_t *chunk, size_t size) {
	chunk_t remaining = { chunk->size - (sizeof(*chunk) + size), 0 };

	chunk->size = size;
	chunk->used = 1;

	*next(chunk) = remaining;	
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

