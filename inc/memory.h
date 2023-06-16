#include <stddef.h> // size_t
#include <unistd.h> // getpagesize
//
#define ALIGNMENT 	sizeof(void *) // TODO
#define PAGESIZE 	getpagesize()

size_t 	align(size_t size, size_t alignment);
void 	*allocate(size_t size);
void	deallocate(void *ptr, size_t size);
