#include <stdalign.h> // alignof
#include <stddef.h>	  // size_t, max_align_t
#include <unistd.h>	  // getpagesize

#define ALIGNMENT alignof(max_align_t)
#define PAGESIZE getpagesize()

#define ALIGN(x, alignment) ((x + alignment - 1) & ~(alignment - 1))

void *allocate(size_t size);
void  deallocate(void *ptr, size_t size);
