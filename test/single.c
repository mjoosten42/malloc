#include "malloc.h"

int main(void) {
	int *ptr = malloc(1000 * 1000);

	*ptr = 42;

	show_alloc_mem();
	free(ptr);
}
