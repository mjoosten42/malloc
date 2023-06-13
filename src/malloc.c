#include "malloc.h"
#include "zone.h"

zone_t	*zones = NULL;

void	*malloc(size_t size) {
	zone_t *zone = new(size);

	append(&zones, zone);

 	return zone + sizeof(*zone);
}
