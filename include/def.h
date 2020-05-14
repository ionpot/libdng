#ifndef LIBDNG_DEF_H
#define LIBDNG_DEF_H

#include <stddef.h>

#define KiB(n) ((n) * 1024)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

typedef size_t index_t;
typedef unsigned char byte;
typedef unsigned int uint;

enum DNG_Status {
	DNG_OK = 0,
	DNG_NO_MEM
};

#endif
