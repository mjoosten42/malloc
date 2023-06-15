#include "malloc.h"
#include "libft.h"
#include <time.h>
#include <stdlib.h>

#define N 32
#define MAX 1024

int main() {
	void *ptr[N] = { 0 };

	srand(time(NULL));

	for (int i = 0; i != N; i++) {
		ptr[i] = malloc(rand() % MAX);
	}	
	

	print();

	for (int i = 0; i != N; i++) {
		free(ptr[i]);
	}

	print();

}

