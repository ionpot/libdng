#ifndef LIBDNG_NODES_H
#define LIBDNG_NODES_H

#include "mempool.h"

#include <stdbool.h>
#include <stddef.h>

struct dngNodes;

struct dngNodes *
dngNodes_create(struct dngMemPool *, size_t content_size);

void *
dngNodes_next(struct dngNodes *);

bool
dngNodes_noMem(const struct dngNodes *);

void
dngNodes_return(struct dngNodes *, void *);

#endif
