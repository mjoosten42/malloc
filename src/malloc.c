#include "malloc.h"
#include "libft.h"
#include "list.h"

t_list	*list = NULL;

void	*malloc(size_t size) {
	t_list	*page = find(&list, has_space, &size);

	ft_printf("page: %s\n", page);
 	(void)size;
 	return (void *)0x42;
}

void	*search(size_t size) {
	(void)size;	
	return NULL;
}

int	has_space(const void *content, void *arg) {
	const t_page	*page = (const t_page *)content;
	size_t			space = *(size_t *)arg;
	size_t			free = page->total - page->used;

	return free >= space;
}


