#ifndef LIBDNG_CONTEXT_H
#define LIBDNG_CONTEXT_H

#include "combat.h"
#include "dice-pool.h"
#include "event.h"
#include "grid.h"
#include "mempool.h"
#include "spell-slots.h"

struct dngContext {
	struct dngCombat * combat;
	struct dngDicePool dices;
	struct dngEvent event;
	struct dngGrid grid;
	struct dngMemPool * mempool;
	struct dngSpellSlots slots;
};

struct dngContext *
dngContext_create(void);

void
dngContext_destroy(struct dngContext *);

enum dngEvent_Id
dngContext_nextEvent(struct dngContext *);

void
dngContext_reset(struct dngContext *);

#endif
