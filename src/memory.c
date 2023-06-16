#include "memory.h"
#include <sys/mman.h>	// mmap
#include <errno.h> 		// errno

#include "libft.h" // TODO: remove

size_t align(size_t number, size_t alignment) {
	size_t minus_one = alignment - 1;

	return (number + minus_one) & ~minus_one;
}

void *allocate(size_t size) {
	int 	prot = PROT_READ | PROT_WRITE;
	int 	flags = MAP_ANONYMOUS | MAP_PRIVATE;
	void 	*ptr = mmap(NULL, size, prot, flags, -1, 0);
	
	ft_printf("mmap: %p\n", ptr);

	if (ptr == MAP_FAILED) {
		ptr = NULL;
		perror("mmap"); // TODO: remove
		errno = ENOMEM;
	}

	return ptr;
}	

