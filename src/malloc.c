#include "impl.h"	// _malloc
#include "memory.h"	// align, ALIGNMENT

#include "debug.h"	// TODO: #ifdef
#include "libft.h"  // TODO: remove

#include <execinfo.h> // TODO: remove

int 	saving = 1;

void	*malloc(size_t size) {
	ft_printf("malloc: %d\n", size);

	void *ret = _malloc(align(size, ALIGNMENT));
		
	if (ret && saving) {
		saving = 0;
		save(ret, size);
		saving = 1;
	}

	return ret;
}

