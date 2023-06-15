#include "malloc.h"
#include "zone.h"

zone_t	*zones = NULL;

void	*malloc(size_t size) {
	ft_printf("malloc: %d\n", size);
	
	size = align(size, ALIGNMENT);

	chunk_t *chunk = find(&zones, size);

	if (!chunk) {
		zone_t *zone = new(size);

		if (!zone) {
			return NULL;
		}
	
		append(&zones, zone);
		
		chunk = find(&zone, size);
	}

	take(chunk, size);

	if (size == 73728) {
		zones = NULL;
	}

 	return mem(chunk);
}

void print() {
	for (zone_t *zone = zones; zone != NULL; zone = zone->next) {
		ft_printf("zone: %p:\n", zone);
		
		for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
			ft_printf("\t%p %s size: %d\n", \
				chunk, chunk->used ? "+++" : "---", chunk->size);
		}

		ft_printf("\n");
	}
}
