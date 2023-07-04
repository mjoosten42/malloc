#ifndef DEBUG_H
#define DEBUG_H

#include "libft.h" // ft_printf"

#include <stddef.h> // size_t

#ifdef DEBUG
	#define LOG(format, ...) ft_printf(format, __VA_ARGS__)
#else
	#define LOG(format, ...)
#endif

#define LOCKED(x)            \
	{                        \
		static int lock = 0; \
                             \
		if (!lock) {         \
			lock = 1;        \
			x;               \
			lock = 0;        \
		}                    \
	}

struct log {
	struct log *next;
	void	   *ptr;
	size_t		size;
	void	  **stack;
	size_t		stack_size;
};

typedef struct log log_t;

void save_log(void *ptr, size_t size);
<<<<<<< HEAD
void show_logs(void);

size_t	nb_pointers(void);
void	*pointers(void);

log_t *get_log(void *ptr);
=======
void print_log(void);
>>>>>>> parent of 36a1521... Added fixed-size log

#endif
