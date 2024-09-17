#ifndef ZONE_H
#define ZONE_H

#include "chunk.h"

#include <stddef.h> // size_t

#define TINY (1 << 8)
#define SMALL (1 << 14)
#define LARGE (1 << 20)

/* [ ZONE  ]
 * [ CHUNK ] 	CHUNKSIZE
 * [ ..... ]	chunk->size
 * etc...
 * [ CHUNK ]	zero size
 */

// page header
struct zone {
	struct zone *next;
	struct zone *prev;
	size_t		 capacity;
	chunk_t		 chunk[];
};

typedef struct zone zone_t;

typedef struct {
	zone_t *tiny;
	zone_t *small;
	zone_t *large;
} table_t;

zone_t *map(size_t size);
void	unmap(zone_t *zone);
void	push_back(zone_t *head, zone_t *new);
zone_t *find_zone(chunk_t *chunk);
void	clean(zone_t *zone);

zone_t *table_get(size_t size);
void	init(void);
int		table_contains(table_t *table, zone_t *zone);

int		is_used(zone_t *zone);
zone_t *first_chunk_to_zone(chunk_t *chunk);

size_t	 lst_size(zone_t *zones);
zone_t **zone_list(zone_t *zones);

#endif // ZONE_H
