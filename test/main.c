#include "malloc.h"
#include "libft.h"

int main() {
	void*	ptr = malloc(4);

	ft_printf("%p\n", ptr);
	
	free(ptr);
}
