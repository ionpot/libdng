#ifndef LIBDNG_DEBUG_H
#define LIBDNG_DEBUG_H

#include <stdio.h>

#ifdef NDEBUG
#define DEBUG 0
#else
#define DEBUG 1
#endif

#define debug_print(M, ...) \
	fprintf(stderr, M, ##__VA_ARGS__)

#define debug_prefix(M, ...) \
	debug_print("[%s:%d] " M, __FILE__, __LINE__, ##__VA_ARGS__)

#define debug_wrap(x) \
	do { if (DEBUG) x; } while (0)

#define debug(M, ...) \
	debug_wrap(debug_prefix(M "\n", ##__VA_ARGS__))

#endif
