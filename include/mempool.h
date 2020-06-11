#ifndef LIBDNG_MEMPOOL_H
#define LIBDNG_MEMPOOL_H

#include <stddef.h>

struct DNG_MemPool;

struct DNG_MemPool *
DNG_MemPool_create(size_t growth_size);

void
DNG_MemPool_destroy(struct DNG_MemPool *);

void *
DNG_MemPool_alloc(struct DNG_MemPool *, size_t request);

void
DNG_MemPool_free(struct DNG_MemPool *, void * address);

#endif
