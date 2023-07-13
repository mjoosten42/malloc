#include <stdalign.h> // alignof
#include <stddef.h>	  // size_t, max_align_t
#include <unistd.h>	  // getpagesize

#define ALIGNMENT alignof(max_align_t)
#define PAGESIZE getpagesize()

void *allocate(size_t size);
void  deallocate(void *ptr, size_t size);

size_t align(size_t size, int alignment);
