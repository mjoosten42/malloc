#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE	32
#define MAX 	100

int main(void) {
	srand(time(NULL));

	void	*ptrs[SIZE] = { 0 };
	int		used[SIZE] = { 0 };
	
	size_t	max = rand();

	for (size_t i = 0; i != max; i++) {
		size_t	r = rand() % SIZE;

		if (used[r]) {
			free(ptrs[r]);
			used[r] = 0;
		} else {
			ptrs[r] = malloc(1 + rand() % MAX);
			if (!ptrs[r]) {
				return 1;
			}
			used[r] = 1;
			write(-1, ptrs[r], 1);			
		}
	}



}
