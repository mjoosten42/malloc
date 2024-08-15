#include "malloc.h"

int main(void) {
	int *ptr = malloc(sizeof(int));

	*ptr = 42;

	free(ptr);
	show_alloc_mem();
}
