#include "debug.h"

#include <stdint.h> // uintptr_t
#include "impl.h"	// zones
#include "malloc.h" // show_alloc_mem
#include "malloc.h"
#include "zone.h" // zone_t

#include <signal.h> // raise
#include <stdlib.h> // qsort

void show_alloc_mem(void) {
	zone_t **array = zone_list(zones);

	if (!array) {
		perror("malloc: show_alloc_mem");
		return;
	}

	while (*array++) {
		zone_t	*zone  = *array;
		chunk_t *chunk = zone->chunk;
		char	*type  = chunk->size > LIMIT ? "LARGE" : "SMALL";

		ft_printf("%s : %p\n", type, (void *)zone);

		for (; chunk->size; chunk = next(chunk)) {
			ft_printf("%p - %p : %lu bytes\n",
					  chunk->memory,
					  (void *)next(chunk),
					  chunk->size);
		}
	}

	_free(array);
}

void show_alloc_mem_ex(void) {}

void show(void) {
	zone_t **array = zone_list(zones);
	zone_t	*zone  = NULL;

	if (!array) {
		perror("malloc: show");
		return;
	}

	while ((zone = *array++)) {
		show_zone(zone);
	}

	_free(array);
}

void show_zone(zone_t *zone) {
	ft_printf("----\t%p | %lu ----\n", (void *)zone, zone->capacity);

	for (chunk_t *chunk = zone->chunk; chunk->size; chunk = next(chunk)) {
		ft_printf("| \t%p | %lu\t%s\n",
				  chunk->memory,
				  chunk->size,
				  chunk->used ? "x" : " ");
	}
}

void mwrite(size_t min) {
	for (zone_t *zone = zones; zone != NULL; zone = zone->next) {
		for (chunk_t *chunk = zone->chunk; chunk->size; chunk = next(chunk)) {
			write_strings((const char *)chunk->memory, chunk->size, min);
		}
	}
}

void write_strings(const char *str, size_t len, size_t min) {
	const char *end = str + len;

	while (str < end) {
		size_t i = 0;

		while (str < end && !ft_isprint(*str)) {
			str++;
		}

		while (str + i < end && ft_isprint(str[i])) {
			i++;
		}

		if (i >= min) {
			ssize_t ret	 = write(1, str, i);
			ssize_t nret = write(1, "\n", 1);

			if (ret < 0 || nret < 0) {
				perror("write");
				return;
			}
		}

		str += i;
	}
}

void sanitize() {
	for (zone_t *zone = zones; zone; zone = zone->next) {
		if (zone->prev && zone->prev->next != zone) {
			ft_printf("list error\n");
			raise(SIGTRAP);
		}

		if (!zone->capacity || zone->capacity % PAGESIZE) {
			ft_printf("corrupt capacity: %ld\n", zone->capacity);
			raise(SIGTRAP);
		}

		for (chunk_t *chunk = zone->chunk; chunk->size; chunk = next(chunk)) {
			if (chunk->size % ALIGNMENT) {
				ft_printf("corrupt size: %ld\n", chunk->size);
				raise(SIGTRAP);
			}

			if (chunk->used != 0 && chunk->used != 1) {
				ft_printf("corrupt used: %d\n", chunk->used);
				raise(SIGTRAP);
			}

			if (chunk != zone->chunk && zone->capacity > (size_t)PAGESIZE) {
				ft_printf("multiple chunks in multipage zone\n");
				raise(SIGTRAP);
			}
		}
	}
}

void show_around(zone_t *ptr, size_t range) {
	size_t _range = range * PAGESIZE;

	for (zone_t *zone = zones; zone; zone = zone->next) {
		uintptr_t diff = 0;

		if (ptr > zone) {
			diff = (uintptr_t)ptr - (uintptr_t)zone;
		} else {
			diff = (uintptr_t)zone - (uintptr_t)ptr;
		}

		if (diff < _range) {
			ft_printf("%p\n", zone);
		}
	}
}

zone_t *find_zone(zone_t *ptr) {
	zone_t *closest = NULL;

	for (zone_t *zone = zones; zone; zone = zone->next) {
		if (zone > closest && zone <= ptr) {
			closest = zone;
		}
	}

	return closest;
}

int compare(const void *first, const void *second) {
	return *(zone_t **)first < *(zone_t **)second;
}
