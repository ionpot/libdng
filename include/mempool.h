#ifndef LIBDNG_MEMPOOL_H
#define LIBDNG_MEMPOOL_H

#include <stddef.h>

struct DNG_MemPool;

struct DNG_MemPool *
DNG_MemPoolCreate(size_t growth_size);

void
DNG_MemPoolDestroy(struct DNG_MemPool *);

void *
DNG_MemPoolAlloc(struct DNG_MemPool *, size_t request);

void
DNG_MemPoolFree(struct DNG_MemPool *, void * address);

#endif
