#include "malloc.h"
#include "libft.h"
#include <time.h>
#include <stdlib.h>
#include "debug.h"

int main(void) {
	void *ptr = malloc(8);
	void *a = malloc(4096);

	free(ptr);

	(void)a;

	print_zones();
}
