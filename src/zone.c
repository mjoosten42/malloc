#include "malloc.h" // PAGESIZE
#include "zone.h"
#include <sys/mman.h>

zone_t *new(size_t size) {
	size_t 	aligned = align(size + sizeof(zone_t), PAGESIZE);
	zone_t 	*zone = allocate(aligned);

	ft_printf("mmap: %p\n", zone);

	if (!zone) {
		return NULL;
	}

	zone->next = NULL;
	zone->previous = NULL;
	zone->capacity = aligned;
	zone->size = size;
	
	alloc_t *alloc = &zone->allocations;

	alloc->next = NULL;
	alloc->size = size;

	return zone;
}

zone_t *find_free(zone_t **zones, size_t size) {
	for (zone_t *zone = *zones; zone != NULL; zone = zone->next) {
		size_t free = zone->capacity - zone->size;

		// zone as a whole has enough space, but it might not be continous
		if (free >= size) {
			
		}
	}
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

size_t align(size_t number, size_t alignment) {
	size_t minus_one = alignment - 1;

	return (number + minus_one) & ~minus_one;
}

zone_t *allocate(size_t size) {
	int prot = PROT_READ | PROT_WRITE;
	int flags = MAP_ANONYMOUS | MAP_PRIVATE;

	return mmap(NULL, size, prot, flags, -1, 0);
}	


