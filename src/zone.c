#include "malloc.h"		// PAGESIZE
#include "zone.h"
#include <sys/mman.h>	// mmap
#include <errno.h>		// errno

zone_t *new(size_t size) {
	size_t 	header_size = sizeof(zone_t) + 2 * sizeof(alloc_t);
	size_t 	capacity = align(size + header_size, PAGESIZE);
	zone_t 	*zone = allocate(capacity);

	if (!zone) {
		return NULL;
	}

	zone->next = NULL;
	zone->previous = NULL;

	alloc_t *chunk = chunks(zone);

	*chunk = (alloc_t){ capacity - header_size, 0 };

	*next(chunk) = (alloc_t){ 0, 0 };

	return zone;
}

alloc_t *find(zone_t **zones, size_t size) {
	for (zone_t *zone = *zones; zone != NULL; zone = zone->next) {
		for (alloc_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
			if (!chunk->used && chunk->size >= size) {
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
	for (alloc_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
		if (!chunk->used) {
			for (alloc_t *n = next(chunk); n->size && !n->used; n = next(n)) {
				ft_printf("adding %d\n", n->size);
				chunk->size += n->size + sizeof(*chunk);
			}
		}
	}
}

alloc_t *chunks(zone_t *zone) {
	return (alloc_t *)((size_t)zone + sizeof(*zone));
}

alloc_t *next(alloc_t *alloc) {
	alloc_t *ret = (alloc_t *)((size_t)alloc + alloc->size);

	if (ret == alloc) {
		ft_printf("next: infinite loop\n");
		exit(1);
	}

	return ret;
}

void 	*mem(alloc_t *alloc) {
	return (void *)((size_t)alloc + sizeof(*alloc));
}

void 	take(alloc_t *alloc, size_t size) {
	alloc_t remaining = { alloc->size - (sizeof(*alloc) + size), 0 };

	alloc->size = size;
	alloc->used = 1;

	*next(alloc) = remaining;	
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

