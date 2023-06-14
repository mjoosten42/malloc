#include "malloc.h"
#include "zone.h"

void free(void *ptr) {
	for (zone_t *zone = zones; zone != NULL; zone = zone->next) {
		for (alloc_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
			if (mem(chunk) == ptr) {
				ft_printf("found ptr\n");
				print();
				chunk->used = 0;

				ft_printf("set used 0\n");
				print();
				merge(zone);

				return ;
			}
		}
	}

	ft_printf("free error\n");
}

