#include <stddef.h> // size_t
#include <unistd.h> // getpagesize

#define ALIGNMENT 	sizeof(void *) // TODO
#define PAGESIZE 	getpagesize()

#define ALIGN(x, alignment) ((x + alignment - 1) & ~(alignment - 1))

void 	*allocate(size_t size);
void	deallocate(void *ptr, size_t size);
