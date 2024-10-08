#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdalign.h>
#include <unistd.h>
#include <libgen.h>

#define SIZE	32
#define MAX 	8096

int main(int argc, char *argv[]) {
	void	*ptrs[SIZE] = { 0 };
	int		used[SIZE] = { 0 };

	if (argc < 2) {
		printf("Usage: %s number\n", basename(argv[0]));
		exit(1);
	}

	srand(time(NULL));
	
	size_t	max = strtol(argv[1], NULL, 10);
	for (size_t i = 0; i != max; i++) {
		size_t	r = rand() % SIZE;

		if (used[r]) {
			size_t s = rand();
		
			if (s % 2) {
				ptrs[r] = realloc(ptrs[r], 1 + rand() % MAX);
				if (!ptrs[r]) {
					return 1;
				}
			} else {
				free(ptrs[r]);
				used[r] = 0;
			}
		} else {
			ptrs[r] = malloc(1 + rand() % MAX);
			if (!ptrs[r]) {
				return 1;
			}
			used[r] = 1;
			write(-1, ptrs[r], 1);			
		}
	}

	show_alloc_mem();
}
