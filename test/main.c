#include "malloc.h"
#include "libft.h"
#include <time.h>
#include <stdlib.h>

#define N 32
#define MAX 1024

int main() {
	void *ptrs[N] = { 0 };

	srand(time(NULL));

	for (int i = 0; i != N; i++) {
		ptrs[i] = malloc(rand() % MAX);
	}


	for (int i = 0; i != N; i++) {
		free(ptrs[i]);
	}

	print();
}

