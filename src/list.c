#include "list.h"
#include "libft.h" // t_list

t_list	*find(t_list **lst, list_fun fun, void *arg) {
	t_list	*ptr = *lst;

	while(ptr) {
		if (fun(ptr->content, arg)) {
			return ptr;
		}
		ptr = ptr->next;
	}

	return NULL;
}

