#ifndef REGION_H
#define REGION_H

#include <stddef.h> // size_t

struct region {
	struct region*	next;
	size_t 			capacity;
	size_t 			size;
};

typedef struct region region_t;

typedef int (*list_fun)(region_t *region, void *arg);

region_t 	*new(size_t size);
region_t 	*append(region_t **lst, region_t *new);
//region_t 	*remove(region_t **lst, list_fun fun, void *arg);
region_t 	*find(region_t **lst, list_fun fun, void *arg);

size_t 		align(size_t size, size_t alignment);
void 		*allocate(size_t size);

#endif // REGION_H
