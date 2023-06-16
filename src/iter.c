#include "iter.h"
#include "zone.h"
#include "stdint.h" // uintptr_t

#include "libft.h" // TODO: remove
#include "debug.h" // TODO: remove

iter_t iter(zone_t *zone) {
	chunk_t *chunk = NULL;

	if (zone) {
		chunk = chunks(zone);
	}

	return (iter_t){ zone, chunk };
}

iter_t 	find(zone_t *zones, fun f, void *arg) {
	for (iter_t it = iter(zones); ok(&it); iter_next(&it)) {
		if (f(&it, arg)) {
			return it;
		}
	}

	return (iter_t){ NULL, NULL };
}

iter_t *iter_next(iter_t *it) {
	it->chunk = next(it->chunk);

	if (it->chunk->size == 0) {
		it->zone = it->zone->next;
		it->chunk = NULL;
	
		if (it->zone) {
			it->chunk = chunks(it->zone);
		}
	}

	return it;
}

chunk_t *chunks(zone_t *zone) {
	return (chunk_t *)((uintptr_t)zone + sizeof(*zone));
}

chunk_t *next(chunk_t *chunk) {
	size_t	offset = sizeof(*chunk) + chunk->size;
	chunk_t *ret = (chunk_t *)((uintptr_t)chunk + offset);

	// TODO: remove
	if (ret == chunk) {
		ft_printf("next: infinite loop\n");
		exit(1);
	}

	chunk = ret;

	return ret;
}

int ok(iter_t *iter) {
	return iter->zone != NULL;
}

