#ifndef DEBUG_H
#define DEBUG_H

#include <stddef.h> // size_t
#include <stdio.h>	// printf"
#include <pthread.h>
#include "impl.h" // mutex

#ifdef VERBOSE
	#define LOG(format, ...) printf(format, __VA_ARGS__)
#else
	#define LOG(format, ...)
#endif

#define LOCKED(...)          \
	{                        \
		static int lock = 0; \
							 \
		if (!lock) {         \
			lock = 1;        \
			__VA_ARGS__;     \
			lock = 0;        \
		}                    \
	}

#endif
