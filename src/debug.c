#include "debug.h"

#include "impl.h"	// zones
#include "malloc.h" // show_alloc_mem
#include "zone.h"	// zone_t

#include <stdio.h>
#include <stdlib.h> // qsort

static int compare(const void *first, const void *second) {
	return *(zone_t **)first > *(zone_t **)second;
}

void show_alloc_mem(void) {
	size_t	size = lst_size(zones);
	zone_t *array[size];
	size_t	i = 0;

	for (zone_t *zone = zones; zone; zone = zone->next) {
		array[i++] = zone;
	}

	qsort((void *)array, size, sizeof(zone_t *), compare);

	for (size_t i = 0; i != size; i++) {
		zone_t	*zone  = array[i];
		chunk_t *chunk = chunks(zone);
		chunk_t *end   = zone_end(zone);

		printf(
			"%s : %p\n", chunk->size > LIMIT ? "LARGE" : "SMALL", (void *)zone);

		for (; chunk != end; chunk = next(chunk)) {
			printf("%p - %p : %lu bytes\n",
				   mem(chunk),
				   (void *)next(chunk),
				   chunk->size);
		}
	}
}

void show_alloc_mem_ex(void) {
	printf("show_alloc_mem_ex\n");
	for (zone_t *zone = zones; zone != NULL; zone = zone->next) {
		chunk_t *end = zone_end(zone);

		printf("# \t%p | %lu\n", (void *)zone, zone->capacity);

		for (chunk_t *chunk = chunks(zone); chunk != end; chunk = next(chunk)) {
			printf("| \t%p | %lu %s\n",
				   mem(chunk),
				   chunk->size,
				   chunk->used ? "x" : " ");
		}
	}
}
