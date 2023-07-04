#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h> // printf"
#include <stddef.h> // size_t

#ifdef DEBUG
	#define LOG(format, ...) printf(format, __VA_ARGS__)
#else
	#define LOG(format, ...)
#endif

#define LOCKED(...)            \
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
