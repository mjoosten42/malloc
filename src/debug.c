#include "debug.h"		
#include "execinfo.h"	// backtrace
#include "impl.h"		// _malloc

#include <stdio.h>		// printf

static void	*stack_log = NULL;

void save_log(void *ptr, size_t size) {
	void	*stack[MAX_STACK];
	int		ret = backtrace(stack, MAX_STACK);
	log_t	*log = _malloc(sizeof(*log));

	log->next = stack_log;
	log->ptr = ptr;
	log->size = size;
	log->stack = _malloc(size * sizeof(void *));
	log->stack_size = ret;

	stack_log = log;
}

void print_log() {
	printf("log:\n");
	for (log_t *log = stack_log; log; log = log->next) {
		printf("%p %zu\n", log->ptr, log->size);

		backtrace_symbols_fd(log->stack, log->stack_size, 1);
	}
}

void print_zones() {
	for (zone_t *zone = zones; zone != NULL; zone = zone->next) {
		printf("capacity: %zu\n", zone->capacity);
		printf("\t%p | %s %zu\n", (void *)zone, "zone ", sizeof(*zone));
	
		for (chunk_t *chunk = chunks(zone); chunk->size; next(chunk)) {
			printf("\t%p | %s %zu\n", (void *)chunk, "chunk", sizeof(*chunk));
			printf("\t%p | %s %zu\n", mem(chunk), \
				 chunk->used ? "+++++" : "-----", chunk->size);
		}

		printf("\n");
	}
}
