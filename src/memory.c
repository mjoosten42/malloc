#include "memory.h"

#include "debug.h" // LOG

#include <errno.h>	  // errno
#include <stdint.h>	  // SIZE_MAX
#include <sys/mman.h> // mmap

void *allocate(size_t size) {
	int	  prot	= PROT_READ | PROT_WRITE;
	int	  flags = MAP_ANONYMOUS | MAP_PRIVATE;
	void *ptr	= mmap(NULL, size, prot, flags, -1, 0);

	LOG("mmap(%lu):\t\t\t%p\n", size, ptr);

	if (ptr == MAP_FAILED) {
		ptr = NULL;
		perror("mmap");
		errno = ENOMEM;
	}

	return ptr;
}

void deallocate(void *ptr, size_t size) {
	LOG("munmap(%p, %lu)\n", ptr, size);

	int ret = munmap(ptr, size);

	if (ret < 0) {
		perror("munmap");
	}
}

size_t align(size_t size, int alignment) {
	return (size + alignment - 1) & ~(alignment - 1);
}
