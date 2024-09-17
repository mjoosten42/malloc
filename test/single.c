#include "malloc.h"

int main(void) {
	int *ptr = malloc(10);

	*ptr = 42;

	show_alloc_mem_ex();
	free(ptr);
}
