#include "debug.h"
#include "impl.h" // pagesize
#include "malloc.h"
#include "memory.h" // align

#include <pthread.h>
#include <stdint.h> // SIZE_MAX

export void *calloc(size_t count, size_t size) {
	size_t total = count * size;

	if (!total ||  SIZE_MAX / count < size) {
		return NULL;
	}

	pthread_mutex_lock(&mutex);
	void *ret = _malloc(align(total, PAGESIZE));

	if (ret) {
		ft_bzero(ret, total);
	}

	LOG("calloc(%lu, %lu)\t%p\n", count, size, ret);
	pthread_mutex_unlock(&mutex);

	return ret;
}
