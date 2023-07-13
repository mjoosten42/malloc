#include "debug.h"
#include "impl.h"
#include "malloc.h"

#include <pthread.h>
#include <stdint.h> // SIZE_MAX

void *calloc(size_t count, size_t size) {
	size_t total = count * size;

	if (SIZE_MAX / count < size) {
		return NULL;
	}

	pthread_mutex_lock(&mutex);
	void *ret = _malloc(align(total, PAGESIZE));

	ft_bzero(ret, total);

	LOG("calloc(%lu, %lu)\t%p\n", count, size, ret);
	pthread_mutex_unlock(&mutex);

	return ret;
}
