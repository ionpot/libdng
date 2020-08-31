#ifndef LIBDNG_DEBUG_H
#define LIBDNG_DEBUG_H

#include <stdio.h>

#ifdef NDEBUG
#define DEBUG 0
#else
#define DEBUG 1
#endif

#define dngDebug_print(M, ...) \
	fprintf(stderr, "[%s:%d] " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define dngDebug(M, ...) \
	do { if (DEBUG) dngDebug_print(M, ##__VA_ARGS__); } while (0)

#endif
