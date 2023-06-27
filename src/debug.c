#include "debug.h"

#include "impl.h" // _malloc
#include "libft.h"
#include "malloc.h" // show_alloc_mem
#include "memory.h"

#include <stdint.h>

static log_t *logs	   = NULL;
static int	  len	   = 0;

void save_log(void *ptr, size_t size) {
	if (!logs) {
		logs = allocate(1024 * PAGESIZE);
	}

	logs[len] = (log_t){ ptr, size, 0 };
	len++;
}

void show_logs(void) {
	ft_printf("        ptr    | freed | size\n");
	for (int i = 0; i < len; i++) {
		log_t *log	 = &logs[i];
		char  *freed = log->freed ? GREEN "Yes  " DEFAULT : RED "No   " DEFAULT;

		ft_printf("%p | %s | %d\n", log->ptr, freed, log->size);
	}

	fflush(stdout);
}

log_t *get_log(void *ptr) {
	for (int i = 0; i < len; i++) {
		log_t *log = &logs[i];

		if (log->ptr == ptr) {
			return log;
		}
	}

	return NULL;
}

void show_alloc_mem(void) {
	ft_printf("--- Zones ---\n");
	for (zone_t *zone = zones; zone != NULL; zone = zone->next) {
		ft_printf("%p | %d\n", (void *)zone, zone->capacity);

		for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
			ft_printf("\t%p | %s | %d\n",
					  mem(chunk),
					  chunk->used ? "x" : " ",
					  chunk->size);
		}

		ft_printf("%p\n", zone + zone->capacity);
	}
}

void show_alloc_mem_ex(void) {}
