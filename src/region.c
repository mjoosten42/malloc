#include "malloc.h" // PAGESIZE
#include "region.h"
#include <sys/mman.h>

region_t *new(size_t size) {
	size_t 		aligned = align(size + sizeof(region_t), PAGESIZE);
	region_t 	*region = allocate(aligned);

	ft_printf("mmap: %p\n", region);

	if (!region) {
		return NULL;
	}

	region->next = NULL;
	region->capacity = aligned;
	region->size = size;

	return region;
}

region_t *append(region_t **lst, region_t *new) {
	region_t *region = *lst;

	while (region) {
		if (!region->next) {
			region->next = new;
			break;
		}
		region = region->next;
	}

	return new;
}

region_t	*find(region_t **lst, list_fun fun, void *arg) {
	region_t *ptr = *lst;

	while (ptr) {
		if (fun(ptr, arg)) {
			return ptr;
		}
		ptr = ptr->next;
	}

	return NULL;
}

size_t align(size_t number, size_t alignment) {
	size_t minus_one = alignment - 1;

	return (number + minus_one) & ~minus_one;
}

void *allocate(size_t size) {
	int prot = PROT_READ | PROT_WRITE;
	int flags = MAP_ANONYMOUS | MAP_PRIVATE;

	return mmap(NULL, size, prot, flags, -1, 0);
}	


