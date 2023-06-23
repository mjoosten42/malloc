#include "debug.h"		
#include "execinfo.h"	// backtrace
#include "impl.h"		// _malloc

#include "libft.h"

#define MAX_STACK 32

static void	*stack_log = NULL;
static int	lock = 0;

__attribute((constructor)) void init(void) {
	atexit(print_zones);
}

void save_log(void *ptr, size_t size) {
	if (!lock) {
		lock = 1;
		
		void	*stack[MAX_STACK];
		int		ret = backtrace(stack, MAX_STACK);
		log_t	*log = _malloc(sizeof(*log));
	
		log->next = stack_log;
		log->ptr = ptr;
		log->size = size;
		log->stack = _malloc(size * sizeof(void *));
		log->stack_size = ret;

		for (int i = 0; i != ret; i++) {
			log->stack[i] = stack[i];
		}
	
		stack_log = log;

		lock = 0;
	}
}

void print_log(void) {
	ft_printf("log:\n");
	for (log_t *log = stack_log; log; log = log->next) {
		ft_printf("%p %d\n", log->ptr, log->size);

		backtrace_symbols_fd(log->stack, log->stack_size, 1);
	}

	fflush(stdout);
}

void print_zones(void) {
	ft_printf("--- Zones ---\n");
	for (zone_t *zone = zones; zone != NULL; zone = zone->next) {
		ft_printf("capacity: %d\n", zone->capacity);
		ft_printf("\t%p | %s %d\n", (void *)zone, "zone ", ZONESIZE);
	
		for (chunk_t *chunk = chunks(zone); chunk->size; chunk = next(chunk)) {
			ft_printf("\t%p | %s %d\n", (void *)chunk, "chunk", CHUNKSIZE);
			ft_printf("\t%p | %s %d\n", mem(chunk), \
				 chunk->used ? "+++++" : "-----", chunk->size);
		}

		ft_printf("\n");
	}
}
