#ifndef LIBDNG_MEMPOOL_H
#define LIBDNG_MEMPOOL_H

#include <stddef.h>

struct dngMemPool;

struct dngMemPool *
dngMemPool_create(size_t growth_size);

void
dngMemPool_destroy(struct dngMemPool *);

void *
dngMemPool_alloc(struct dngMemPool *, size_t request);

void
dngMemPool_free(struct dngMemPool *, void * address);

#endif
