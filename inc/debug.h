#ifndef DEBUG_H
#define DEBUG_H

#include <stddef.h>	// size_t

#define MAX_STACK 32

struct log {
	struct log *next;
	void 		*ptr;
	size_t 		size;
	void 		*stack;
	size_t		stack_size;
};

typedef struct log log_t;

void 	save(void *ptr, size_t size);
void	show_log();
void 	print(); // TODO: remove

#endif 
