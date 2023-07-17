#include "debug.h"
#include "impl.h"

void *memalign(size_t alignment, size_t size) {
	LOG("memalign(%lu, %lu) -> malloc\n", alignment, size);

	(void)alignment;

	return malloc(size);
}
