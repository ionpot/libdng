#ifndef LIBDNG_INTBAG_H
#define LIBDNG_INTBAG_H

#define dngIntBag_MAX_VALUE 99

#include "mempool.h"

struct dngIntBag;

struct dngIntBag *
dngIntBag_create(struct dngMemPool *);

int
dngIntBag_next(struct dngIntBag *);

#endif
