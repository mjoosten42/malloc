#include "impl.h"	// _malloc
#include "memory.h"	// align, ALIGNMENT

#include "debug.h"	// TODO: #ifdef
#include "libft.h"  // TODO: remove

#include <execinfo.h> // TODO: remove

void	*malloc(size_t size) {
	LOCKED(printf("malloc: %zu\n", size));

	void *ret = _malloc(align(size, ALIGNMENT));
		
	if (ret) {
//		LOCKED(save(ret, size));
	}

	return ret;
}

