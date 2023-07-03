#ifndef DEBUG_H
#define DEBUG_H

#include "libft.h" // ft_printf"

#include <stddef.h> // size_t

#ifdef DEBUG
	#define LOG(format, ...) ft_printf(format, __VA_ARGS__)
#else
	#define LOG(format, ...)
#endif

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define DEFAULT "\033[0m"

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
	void  *ptr;
	size_t size;
	int	   freed;
};

typedef struct log log_t;

void save_log(void *ptr, size_t size);
void show_logs(void);

size_t	nb_pointers(void);
void	*pointers(void);

log_t *get_log(void *ptr);

#endif
