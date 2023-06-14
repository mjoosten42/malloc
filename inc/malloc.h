#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h> // size_t

#include "../lib/libft/include/libft.h" // TODO: remove

void 	free(void *ptr);
void 	*malloc(size_t size);
void 	*realloc(void *ptr, size_t size);

void 	print(); // TODO: remove

#endif // MALLOC_H
