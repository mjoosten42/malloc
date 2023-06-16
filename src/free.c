#include "zone.h"
#include "iter.h"
#include <stdlib.h> // abort
#include "impl.h"	// zones

#include <stdio.h> // TODO: remove

static int 	is_ptr(iter_t *it, void *arg);

void	free(void *ptr) {
	printf("free:   %p\n", ptr);
	
	if (!ptr) {
		return ;
	}

	_free(ptr);
}

void	_free(void *ptr) {
	iter_t it = find(zones, is_ptr, &ptr);

	if (!ok(&it)) {
		abort();
	}

	it.chunk->used = 0;
	
	clean(it.zone);
}

static int is_ptr(iter_t *it, void *arg) {
	return mem(it->chunk) == *(void **)arg;
}

