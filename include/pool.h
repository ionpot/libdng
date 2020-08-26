#ifndef LIBDNG_POOL_H
#define LIBDNG_POOL_H

#include "mempool.h"

#include <stddef.h>

struct dngPool;

struct dngPool *
dngPool_create(struct dngMemPool *, size_t content_size);

void
dngPool_reset(struct dngPool *);

void *
dngPool_next(struct dngPool *);

#endif
