#include "spell-pool.h"

#include "mempool.h"
#include "pool.h"
#include "spell-slot.h"

#define CONTENT_SIZE sizeof(struct dngSpellSlot)

typedef struct dngSpellPool T;

T
dngSpellPool_create(struct dngMemPool * mempool)
{
	return (T){
		.pool = dngPool_create(mempool, CONTENT_SIZE)
	};
}

struct dngSpellSlot *
dngSpellPool_nextSlot(T self)
{
	return dngPool_next(self.pool);
}
