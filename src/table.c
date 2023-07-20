#include "table.h"

#include "libft.h"	// ft_memcpy
#include "memory.h" // PAGESIZE
#include "zone.h"	// push

size_t hash(size_t size) {
	return size / ALIGNMENT;
}

// TODO: only get
zone_t *get(table_t *table, size_t size) {
	size_t index = hash(size);

	if (index >= table->capacity || !table->zones[index]) {
		zone_t *zone = map(size);

		if (!zone) {
			return NULL;
		}

		if (insert(table, zone)) {
			return NULL;
		}
	}

	return table->zones[index];
}

int insert(table_t *table, zone_t *zone) {
	size_t index = hash(zone->size);

	while (index >= table->capacity) {
		if (extend(table)) {
			return 1;
		}
	};

	push(&table->zones[index], zone);

	return 0;
}

int extend(table_t *table) {
	size_t size		= table->bytes;
	size_t new_size = size ? 2 * size : (size_t)PAGESIZE;

	void *tmp = allocate(new_size);

	if (!tmp) {
		return 1;
	}

	if (table->zones) {
		ft_memcpy(tmp, table->zones, table->bytes);
		deallocate(table->zones, table->bytes);
	}

	table->zones	= tmp;
	table->bytes	= new_size;
	table->capacity = new_size / sizeof(zone_t *);

	return 0;
}
