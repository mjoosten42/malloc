#include "malloc.h"
#include "zone.h"
#include "iter.h"

int is_ptr(iter_t *it, void *arg);

void free(void *ptr) {
	ft_printf("free:   %p\n", ptr);
	if (!ptr) {
		return ;
	}

	iter_t it = find(&zones, is_ptr, &ptr);

	if (!ok(&it)) {
		ft_printf("free error\n");
		return ;
	}

	it.chunk->used = 0;
	merge(it.zone);

	//TODO: munmap
}

int is_ptr(iter_t *it, void *arg) {
	return mem(it->chunk) == *(void **)arg;
}

