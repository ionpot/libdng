#ifndef LIBDNG_INT_H
#define LIBDNG_INT_H

#include <stddef.h>

#define dngInt_kib(n) ((n) * 1024)

#define dngInt_min(a, b) ((a) < (b) ? (a) : (b))
#define dngInt_max(a, b) ((a) < (b) ? (b) : (a))

void
dngInt_decr(int *, int);

size_t
dngInt_padSize(size_t);

#endif
