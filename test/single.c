#include "malloc.h"

int main(void) {
	int *ptr = malloc(sizeof(*ptr));

	ptr[0] = 42;

	free(ptr);
}
