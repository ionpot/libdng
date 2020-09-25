#ifndef LIBDNG_SPELL_SLOTS_H
#define LIBDNG_SPELL_SLOTS_H

#include "mempool.h"
#include "nodes.h"
#include "spell-slot.h"

struct dngSpellSlots {
	struct dngNodes * nodes;
};

struct dngSpellSlots
dngSpellSlots_create(struct dngMemPool *);

struct dngSpellSlot *
dngSpellSlots_next(struct dngSpellSlots);

void
dngSpellSlots_return(struct dngSpellSlots, struct dngSpellSlot *);

#endif
