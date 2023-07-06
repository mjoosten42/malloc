#include "debug.h"

#include "impl.h" // zones
#include "libft.h"
#include "malloc.h" // show_alloc_mem
#include "zone.h"	// zone_t

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

		printf("%s : %p\n", \
			chunk->size > LIMIT ? "LARGE" : "SMALL", (void *)zone);

		for (; chunk->size; chunk = next(chunk)) {
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
		ft_printf("capacity: %d\n", zone->capacity);
		ft_printf("\t%p\n", zone);

		for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
			ft_printf("\t| \t%p | %d %s\n",
					  mem(chunk),
					  chunk->size,
					  chunk->used ? "x" : " ");
		}
	}
}
