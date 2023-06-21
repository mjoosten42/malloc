#ifndef DEBUG_H
#define DEBUG_H

#include <stddef.h>	// size_t

#define MAX_STACK 32

#define LOCKED(x) {	\
	static int lock = 0;	\
							\
	if (!lock) {			\
		lock = 1;			\
		x;					\
		lock = 0;			\
	}						\
}					

struct log {
	struct log *next;
	void 		*ptr;
	size_t 		size;
	void 		*stack;
	size_t		stack_size;
};

typedef struct log log_t;

void 	save_log(void *ptr, size_t size);
void	print_log();
void 	print_zones(); // TODO: remove

#endif 
