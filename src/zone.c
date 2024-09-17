#include "zone.h"

#include "chunk.h"
#include "impl.h"	// zones
#include "memory.h" // align, PAGESIZE

#include <stdint.h> // uintptr_t
#include <stdlib.h> // qsort

zone_t *map(size_t size) {
	size_t	header_size = sizeof(zone_t) + 2 * CHUNKSIZE;
	size_t	capacity	= align(size + header_size, PAGESIZE);
	zone_t *zone		= allocate(capacity);

	if (!zone) {
		return NULL;
	}

	zone->next	   = NULL;
	zone->prev	   = NULL;
	zone->capacity = capacity;

	*zone->chunk = (chunk_t){ capacity - header_size, 0 };

	// close with zero-size chunk
	*next(zone->chunk) = (chunk_t){ 0, 0 };

	return zone;
}

void unmap(zone_t *zone) {
	if (zone->prev) {
		zone->prev->next = zone->next;
	}

	if (zone->next) {
		zone->next->prev = zone->prev;
	}

	deallocate(zone, zone->capacity);
}

void push_back(zone_t *head, zone_t *new) {
	while (head->next) {
		head = head->next;
	}

	head->next = new;
	new->prev  = head;
}

zone_t *find_zone(chunk_t *chunk) {
	zone_t *zone = table_get(chunk->size);

	for (; zone; zone = zone->next) {
		if (chunk > (chunk_t *)zone &&
			chunk < (chunk_t *)((uintptr_t)zone + zone->capacity)) {
			return zone;
		}
	}

	return NULL;
}

void clean(zone_t *zone) {
	defragment(zone->chunk);

	if (!table_contains(&g_table, zone) && !is_used(zone)) {
		unmap(zone);
	}
}

zone_t *table_get(size_t size) {
	if (table_contains(&g_table, NULL)) {
		init();
	}

	return size > TINY ? size > SMALL ? g_table.large : g_table.small :
						 g_table.tiny;
}

void init(void) {
	size_t allocations = 100;

	g_table.tiny  = map(allocations * TINY);
	g_table.small = map(allocations * SMALL);
	g_table.large = map(LARGE);
}

int table_contains(table_t *table, zone_t *zone) {
	return table->tiny == zone || table->small == zone || table->large == zone;
}

int is_used(zone_t *zone) {
	for (chunk_t *chunk = zone->chunk; chunk->size; chunk = next(chunk)) {
		if (chunk->used) {
			return 1;
		}
	}

	return 0;
}

zone_t *first_chunk_to_zone(chunk_t *chunk) {
	return (zone_t *)((uintptr_t)chunk - sizeof(zone_t));
}

size_t lst_size(zone_t *zones) {
	size_t count = 0;

	for (zone_t *zone = zones; zone; zone = zone->next) {
		count++;
	}

	return count;
}

static int compare(const void *first, const void *second) {
	return *(zone_t **)first < *(zone_t **)second;
}

// returns a sorted, malloc'ed array of zone pointers
zone_t **zone_list(zone_t *zones) {
	size_t	 size  = lst_size(zones);
	zone_t **array = _malloc(align(sizeof(zone_t *) * (size + 1), ALIGNMENT));
	size_t	 i	   = 0;

	if (!array) {
		return NULL;
	}

	for (zone_t *zone = zones; zone; zone = zone->next) {
		array[i++] = zone;
	}

	qsort((void *)array, size, sizeof(zone_t *), compare);

	array[size] = NULL;

	return array;
}
