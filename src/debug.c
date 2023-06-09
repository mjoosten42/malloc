#include "debug.h"

#include "impl.h"	// zones
#include "malloc.h" // show_alloc_mem
#include "zone.h"	// zone_t
#include "malloc.h"

#include <stdlib.h> // qsort

#include <fcntl.h> // open TODO
#include <unistd.h> // dup
					
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
		chunk_t *chunk = zone->chunk;

		ft_printf(
			"%s : %p\n", chunk->size > LIMIT ? "LARGE" : "SMALL", (void *)zone);

		for (; chunk->size; chunk = next(chunk)) {
			ft_printf("%p - %p : %lu bytes\n",
					  chunk->memory,
					  (void *)next(chunk),
					  chunk->size);
		}
	}
}

void show_alloc_mem_ex(void) {}


void show(void) {
	//int fd = open("out", O_CREAT | O_RDWR, 0644);
	//int orig = dup(1);
	//dup2(fd, 1);

	ft_printf("show\n");
	for (zone_t *zone = zones; zone != NULL; zone = zone->next) {
		ft_printf("----\t%p | %lu ----\n", (void *)zone, zone->capacity);

		for (chunk_t *chunk = zone->chunk; chunk->size; chunk = next(chunk)) {
			ft_printf("| \t%p | %lu\t%s\n",
					  chunk->memory,
					  chunk->size,
					  chunk->used ? "x" : " ");
		}
	}

	//dup2(orig, 1);
}
