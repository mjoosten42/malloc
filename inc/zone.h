#ifndef ZONE_H
#define ZONE_H

#include <stddef.h> // size_t
#include <unistd.h> // getpagesize

#define PAGESIZE getpagesize()

struct alloc {
	struct alloc*	next;
	size_t 			size;
};

struct zone {
	struct zone*	next;
	struct zone*	previous;
	struct alloc 	allocations;
	size_t 			capacity;
	size_t 			size;
};

typedef struct alloc 	alloc_t;
typedef struct zone 	zone_t;

zone_t 	*new(size_t size);
zone_t 	*find_free(zone_t **zones, size_t size);
zone_t 	*append(zone_t **lst, zone_t *new);

size_t 	align(size_t size, size_t alignment);
zone_t 	*allocate(size_t size);

#endif // ZONE_H
