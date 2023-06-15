#include "malloc.h"
#include "zone.h"
#include "iter.h"

zone_t	*zones = NULL;

int with_space(iter_t *it, void *arg);

void	*malloc(size_t size) {
	ft_printf("malloc: %d\n", size);
	size = align(size, ALIGNMENT);

	iter_t it = find(&zones, with_space, &size);

	if (!ok(&it)) {
		zone_t *zone = new(size);

		if (!zone) {
			return NULL;
		}
	
		append(&zones, zone);

		it = find(&zone, with_space, &size);
	}

	take(it.chunk, size);

	ft_printf("malloc: %p %d\n", mem(it.chunk), size);

 	return mem(it.chunk);
}

int with_space(iter_t *it, void *arg) {
	size_t 	size = *(size_t *)arg;
	chunk_t *chunk = it->chunk;

	return !chunk->used && chunk->size >= size;
}

#include <stdio.h>

void print() {
	for (zone_t *zone = zones; zone != NULL; zone = zone->next) {
		chunk_t *chunk = chunks(zone);
	
		printf("capacity: %zu\n", zone->capacity);
		printf("\t%p | %s %zu\n", (void *)zone, "zone ", sizeof(*zone));

		for (; chunk->size; chunk = next_chunk(chunk)) {
			printf("\t%p | %s %zu\n", (void *)chunk, "chunk", sizeof(*chunk));
			printf("\t%p | %s %zu\n", mem(chunk), \
				 chunk->used ? "+++++" : "-----", chunk->size);
		}

		printf("\n");
	}
}
