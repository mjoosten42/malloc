#include "debug.h"

#include "execinfo.h" // backtrace
#include "impl.h"	  // _malloc
#include "libft.h"
#include "malloc.h" // show_alloc_mem

#define MAX_STACK 32

static void *stack_log = NULL;

__attribute((constructor)) void init(void) {
	atexit(show_alloc_mem);
}

__attribute((destructor)) void fini(void) {
	show_alloc_mem();
}

void save_log(void *ptr, size_t size) {
	void  *stack[MAX_STACK];
	int	   ret = backtrace(stack, MAX_STACK);
	log_t *log = _malloc(sizeof(*log));

	log->next		= stack_log;
	log->ptr		= ptr;
	log->size		= size;
	log->stack		= _malloc(ret * sizeof(void *));
	log->stack_size = ret;

	for (int i = 0; i != ret; i++) {
		log->stack[i] = stack[i];
	}

	stack_log = log;
}

void print_log(void) {
	ft_printf("log:\n");
	for (log_t *log = stack_log; log; log = log->next) {
		ft_printf("%p %d\n", log->ptr, log->size);

		backtrace_symbols_fd(log->stack, log->stack_size, 1);
		ft_printf("\n");
	}

	fflush(stdout);
}

void show_alloc_mem(void) {
	ft_printf("--- Zones ---\n");
	for (zone_t *zone = zones; zone != NULL; zone = zone->next) {
		ft_printf("capacity: %d\n", zone->capacity);
		ft_printf("\t%p | %s %d\n", (void *)zone, "zone ", ZONESIZE);

		for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
			ft_printf("\t%p | %s %d\n", (void *)chunk, "chunk", CHUNKSIZE);
			ft_printf("\t%p | %s %d\n",
					  mem(chunk),
					  chunk->used ? "+++++" : "-----",
					  chunk->size);
		}

		ft_printf("\n");
	}
}

void show_alloc_mem_ex(void) {}
