#include "libft.h" // t_list

typedef int (*list_fun)(const void *content, void *arg);

t_list	*find(t_list **lst, list_fun fun, void *arg);
