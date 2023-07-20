#ifndef TABLE_H
#define TABLE_H

#include "zone.h" // zone_t

#include <stddef.h> // size_t

typedef struct {
	zone_t **zones;
	size_t	 capacity;
	size_t	 bytes;
} table_t;

extern table_t table;

size_t hash(size_t size);
zone_t *get(table_t *table, size_t size);
int		insert(table_t *table, zone_t *zone);
int		extend(table_t *table);

#endif // TABLE_H
