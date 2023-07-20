#include "debug.h"

#include "impl.h"	// zones
#include "malloc.h" // show_alloc_mem
#include "memory.h" // alignment
#include "zone.h"	// zone_t

#include <signal.h> // raise
#include <stdint.h> // uintptr_t
#include <stdlib.h> // qsort

export void show_alloc_mem(void) {
	zone_t **array = zone_list(zones);

	if (!array) {
		perror("malloc: show_alloc_mem");
		return;
	}

	while (*array++) {
		zone_t	*zone  = *array;
		chunk_t *chunk = zone->chunk;
		char	*type  = chunk->size > 4000 ? "LARGE" : "SMALL";

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

export void show_alloc_mem_ex(void) {}

void print_human_bytes(const char *str, size_t bytes) {
	int i = 0;
	const char letters[] = "\0kmgt";

	while (bytes / 1024) {
		bytes /= 1024;
		i++;
	}

	ft_printf("%s %lu%cb\n", str, bytes, letters[i]);
};

export void show(void) {
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

	print_human_bytes("total:", mem_total());
	print_human_bytes("used: ", mem_used());
	printf("usage: %2.0f%%\n", 100.0 * (float)mem_used() / (float)mem_total());
}

size_t mem_total(void) {
	size_t total = 0;

	for (zone_t *zone = zones; zone; zone = zone->next) {
		total += zone->capacity;
	}

	return total;
}

size_t mem_used(void) {
	size_t used = 0;

	for (zone_t *zone = zones; zone; zone = zone->next) {
		for (chunk_t *chunk = zone->chunk; chunk->size; chunk = next(chunk)) {
			if (chunk->used) {
				used += chunk->size;
			}
		}
	}

	return used;
}
export void show_zone(zone_t *zone) {
	ft_printf("----\t%p | %lu ----\n", (void *)zone, zone->capacity);

	for (chunk_t *chunk = zone->chunk; chunk->size; chunk = next(chunk)) {
		ft_printf("| \t%p | %lu\t%s\n",
				  chunk->memory,
				  chunk->size,
				  chunk->used ? "x" : " ");
	}
}

export void mwrite(size_t min) {
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

export void sanitize() {
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
		}
	}
}

export zone_t *find_zone(zone_t *ptr) {
	zone_t *closest = NULL;

	for (zone_t *zone = zones; zone; zone = zone->next) {
		if (zone > closest && zone <= ptr) {
			closest = zone;
		}
	}

	return closest;
}
