#include "spell-slots.h"

#include "mempool.h"
#include "nodes.h"
#include "spell-slot.h"

#include <assert.h>

typedef struct dngSpellSlots T;

T
dngSpellSlots_create(struct dngMemPool * mempool)
{
	assert(mempool);
	return (T){
		.nodes = dngNodes_create(mempool, sizeof(struct dngSpellSlot))
	};
}

struct dngSpellSlot *
dngSpellSlots_next(T self)
{
	return dngNodes_next(self.nodes);
}

void
dngSpellSlots_return(T self, struct dngSpellSlot * slot)
{
	assert(slot);
	dngNodes_return(self.nodes, slot);
}
