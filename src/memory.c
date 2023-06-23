#include "memory.h"
#include <sys/mman.h>	// mmap
#include <errno.h> 		// errno

#include "debug.h"		// LOG

void *allocate(size_t size) {
	int 	prot = PROT_READ | PROT_WRITE;
	int 	flags = MAP_ANONYMOUS | MAP_PRIVATE;
	void 	*ptr = mmap(NULL, size, prot, flags, -1, 0);
	
	LOG("mmap:\t\t\t%p\t%d\n", ptr, size);

	if (ptr == MAP_FAILED) {
		ptr = NULL;
		perror("mmap"); // TODO: remove
		errno = ENOMEM;
	}

	return ptr;
}

void	deallocate(void *ptr, size_t size) {
	LOG("munmap:\t\t\t%p\t%d\n", ptr, size);

	munmap(ptr, size);
}
