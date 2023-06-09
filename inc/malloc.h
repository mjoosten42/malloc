#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h> // size_t
#include "libft.h" // t_list
#include <unistd.h> // getpagesize

#define PAGESIZE getpagesize()

extern t_list* list;

typedef struct s_page {
	size_t	total;
	size_t	used;
	t_list	*blocks;
}			t_page;

void 	free(void *ptr);
void 	*malloc(size_t size);
void 	*realloc(void *ptr, size_t size);

void	*search(size_t size);
int		has_space(const void *content, void *arg);

#endif // MALLOC_H
