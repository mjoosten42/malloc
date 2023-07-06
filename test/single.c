#include "malloc.h"

int main(void) {
	int *ptr = malloc(8);

	ptr[0] = 42;

	free(ptr);
	show_alloc_mem();
}
