#include "memory.h"

#include "debug.h" // LOG

#include <errno.h>	  // errno
#include <sys/mman.h> // mmap

void *allocate(size_t size) {
	int	  prot	= PROT_READ | PROT_WRITE;
	int	  flags = MAP_ANONYMOUS | MAP_PRIVATE;
	void *ptr	= mmap(NULL, size, prot, flags, -1, 0);

	LOCKED(LOG("mmap(%lu):\t\t%p\n", size, ptr));

	if (ptr == MAP_FAILED) {
		ptr = NULL;
		perror("mmap");
		errno = ENOMEM;
	}

	return ptr;
}

void deallocate(void *ptr, size_t size) {
	LOCKED(LOG("munmap(%p, %lu)", ptr, size));

	int ret = munmap(ptr, size);

	if (ret < 0) {
		perror("munmap");
	}
}
