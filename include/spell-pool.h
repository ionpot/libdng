#ifndef LIBDNG_SPELL_POOL_H
#define LIBDNG_SPELL_POOL_H

#include "mempool.h"
#include "pool.h"
#include "spell-slot.h"

struct dngSpellPool {
	struct dngPool * pool;
};

struct dngSpellPool
dngSpellPool_create(struct dngMemPool *);

struct dngSpellSlot *
dngSpellPool_nextSlot(struct dngSpellPool);

#endif
