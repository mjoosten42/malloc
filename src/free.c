#include "malloc.h"
#include "zone.h"

void free(void *ptr) {
	for (zone_t *zone = zones; zone != NULL; zone = zone->next) {
		for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
			if (mem(chunk) == ptr) {
				chunk->used = 0;

				merge(zone);

				return ;
			}
		}
	}

	ft_printf("free error\n");
}

