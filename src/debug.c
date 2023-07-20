#include "debug.h"

#include "table.h"
#include "libft.h"
#include "iter.h"
#include "impl.h" // export
#include <stdint.h> // uintptr_t

export void show() {
	for (size_t j = 0; j != table.capacity; j++) {
		zone_t *zone = table.zones[j];
		
		if (zone) {
			ft_printf(" --------- %lu -----\t", zone->size);
		}
	}

	ft_printf("\n");
	
	for (size_t i = 0;; i++) { // TODO
		int has_ok = 0;
		
		for (size_t j = 0; j != table.capacity; j++) {
			zone_t *zone = table.zones[j];
			iter_t it = iter(zone);
		
			if (!zone) {
				continue;
			}

			//ft_printf(" - size: %lu - \n\t", zone->size);

			for (size_t k = 0; k != i; k++) {
				next(&it);
				
				if (!ok(&it)) {
					break ;
				}
			}

			if (!ok(&it)) {
				continue;
			}

			
			chunk_t *chunk = it.chunk;

			//if (chunk->size) {
				has_ok = 1;
				ft_printf("%p %lu\t", (uintptr_t)chunk->memory, chunk->size);
			//}
		}

		ft_printf("\n");
	
		if (!has_ok) {
			break ;
		}
	}
}
