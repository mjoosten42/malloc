#include "debug.h"

#include "impl.h" // zones
#include "libft.h"
#include "malloc.h" // show_alloc_mem
#include "zone.h"	// zone_t

void show_alloc_mem(void) {
	printf("show_alloc_mem\n");
	for (zone_t *zone = zones; zone != NULL; zone = zone->next) {
		ft_printf("capacity: %d\n", zone->capacity);
		ft_printf("\t%p | %s %d\n", (void *)zone, "zone ", ZONESIZE);

		for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
			ft_printf("\t%p | %s %d\n",
					  mem(chunk),
					  chunk->used ? "+++++" : "-----",
					  chunk->size);
		}

		ft_printf("\n");
	}
}

void show_alloc_mem_ex(void) {}
