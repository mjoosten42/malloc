#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h> // size_t
#include "libft.h" // t_list
#include <unistd.h> // getpagesize
#include "region.h"

#define PAGESIZE getpagesize()

extern region_t* regions;

void 	free(void *ptr);
void 	*malloc(size_t size);
void 	*realloc(void *ptr, size_t size);

int		has_space(const void *content, void *arg);

#endif // MALLOC_H
