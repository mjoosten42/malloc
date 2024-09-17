#include "debug.h"

#include "impl.h"	// zones
#include "malloc.h" // show_alloc_mem
#include "memory.h" // alignment
#include "zone.h"	// zone_t

#include <signal.h> // raise
#include <stdint.h> // uintptr_t
#include <stdlib.h> // qsort

export void show_alloc_mem(void) {
	size_t total = 0;

	pthread_mutex_lock(&g_mutex);

	ft_printf("%s : %p\n", "TINY", g_table.tiny);
	total += show_alloc_mem_zone(g_table.tiny);

	ft_printf("%s : %p\n", "SMALL", g_table.small);
	total += show_alloc_mem_zone(g_table.small);

	ft_printf("%s : %p\n", "LARGE", g_table.large);
	total += show_alloc_mem_zone(g_table.large);

	ft_printf("Total : %lu bytes\n", total);

	pthread_mutex_unlock(&g_mutex);
}

export void show_alloc_mem_ex(void) {
	pthread_mutex_lock(&g_mutex);

	show_alloc_mem_hex(g_table.tiny);
	show_alloc_mem_hex(g_table.small);
	show_alloc_mem_hex(g_table.large);

	pthread_mutex_unlock(&g_mutex);
}

void show_alloc_mem_hex(zone_t *zone) {
	for (; zone; zone = zone->next) {
		for (chunk_t *chunk = zone->chunk; chunk->size; chunk = next(chunk)) {
			if (chunk->used) {
				ft_printf("%p: ", chunk->memory);

				for (size_t size = 0; size < chunk->size; size += 8) {
					ft_printf("%x ",
							  *(size_t *)((uintptr_t)(chunk->memory) + size));
				}

				ft_printf("\n");
			}
		}
	}
}

size_t show_alloc_mem_zone(zone_t *zone) {
	zone_t **array = zone_list(zone);
	zone_t **tmp   = array;
	size_t	 total = 0;

	if (!array) {
		perror("malloc: show_alloc_mem");
		return 0;
	}

	while (*tmp) {
		for (chunk_t *chunk = (*tmp)->chunk; chunk->size; chunk = next(chunk)) {
			if (chunk->used && (void *)chunk->memory != array) {
				ft_printf("%p - %p : %lu bytes\n",
						  chunk->memory,
						  next(chunk),
						  chunk->size);

				total += chunk->size;
			}
		}

		tmp++;
	}

	_free(array);

	return total;
}
