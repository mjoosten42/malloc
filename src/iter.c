#include "iter.h"
#include "zone.h"
#include "stdint.h" // uintptr_t

#include "libft.h" // TODO: remove

iter_t iter(zone_t **zones) {
	zone_t 	*zone = *zones;
	chunk_t *chunk = NULL;

	if (zone) {
		chunk = chunks(zone);
	}

	return (iter_t){ zone, chunk };
}

iter_t *next(iter_t *it) {
	chunk_t *chunk = it->chunk;

	it->chunk = (chunk_t *)((uintptr_t)chunk + sizeof(*chunk) + chunk->size);

	if (chunk->size == 0) {
		it->zone = it->zone->next;

		if (it->zone) {
			it->chunk = chunks(it->zone);
		}
	}

	return it;
}

iter_t 	find(zone_t **zones, fun f, void *arg) {
	for (iter_t it = iter(zones); ok(&it); next(&it)) {
		if (f(&it, arg)) {
			return it;
		}
	}

	return (iter_t){ NULL, NULL };
}

chunk_t *chunks(zone_t *zone) {
	return (chunk_t *)((uintptr_t)zone + sizeof(*zone));
}

chunk_t *next_chunk(chunk_t *chunk) {
	chunk_t *ret = (chunk_t *)((uintptr_t)chunk + sizeof(*chunk) + chunk->size);

	// TODO: remove
	if (ret == chunk) {
		ft_printf("next: infinite loop\n");
		exit(1);
	}

	return ret;
}

int ok(iter_t *iter) {
	return iter->zone != NULL;
}

