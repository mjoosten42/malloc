#ifndef DEBUG_H
#define DEBUG_H

#include <stddef.h>	// size_t
#include "libft.h"	// ft_printf"

#ifdef DEBUG
	#define LOG(format, ...) ft_printf(format, __VA_ARGS__)
#else
	#define LOG(format, ...)
#endif


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
	void 		**stack;
	size_t		stack_size;
};

typedef struct log log_t;

void 	save_log(void *ptr, size_t size);
void	print_log(void);
void 	print_zones(void);

#endif 
