#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h> // size_t

void 	free(void *ptr);
void 	*malloc(size_t size);
void 	*realloc(void *ptr, size_t size);

#include "debug.h" // TODO

#endif // MALLOC_H
