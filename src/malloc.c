#include "malloc.h"
#include "libft.h"
#include "region.h"

region_t	*regions = NULL;

void	*malloc(size_t size) {
	region_t *region = new(size);

	append(&regions, region);

 	return region + sizeof(*region);
}
