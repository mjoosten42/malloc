#include "memory.h"

#include "debug.h" // LOCKED, LOG

#include <errno.h>	  // errno
#include <sys/mman.h> // mmap

void *allocate(size_t size) {
	int	  prot	= PROT_READ | PROT_WRITE;
	int	  flags = MAP_ANONYMOUS | MAP_PRIVATE;
	void *ptr	= mmap(NULL, size, prot, flags, -1, 0);

	pthread_mutex_unlock(&mutex);
	LOCKED(LOG("mmap(%zu):\t\t%p\n", size, ptr));
	pthread_mutex_lock(&mutex);

	if (ptr == MAP_FAILED) {
		ptr = NULL;
		perror("mmap");
		errno = ENOMEM;
	}

	return ptr;
}

void deallocate(void *ptr, size_t size) {
	pthread_mutex_unlock(&mutex);
	LOCKED(LOG("munmap(%p, %zu)\n", ptr, size));
	pthread_mutex_lock(&mutex);

	int ret = munmap(ptr, size);

	if (ret < 0) {
		perror("munmap");
	}
}
