#include "impl.h"	// _malloc
#include "memory.h"	// align, ALIGNMENT

// TODO: remove
#include "debug.h"	
#include "libft.h"

void	*malloc(size_t size) {
	LOG("malloc(%d):\t\t...\n", size);

	if (!size) {
		return NULL;
	}
	void *ret = _malloc(align(size, ALIGNMENT));
		
	LOG("malloc(%d):", size);
	LOG("\t\t%p\n", ret);

	return ret;
}

