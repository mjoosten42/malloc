#ifndef MALLOC_H
#define MALLOC_H

#include "debug.h" // TODO

#include <stddef.h> // size_t

void  free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

void show_alloc_mem(void);
void show_alloc_mem_ex(void);

#endif // MALLOC_H
