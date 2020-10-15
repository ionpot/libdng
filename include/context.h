#ifndef LIBDNG_CONTEXT_H
#define LIBDNG_CONTEXT_H

#include "combat.h"
#include "dice-pool.h"
#include "event.h"
#include "grid.h"
#include "input-def.h"
#include "int-bag.h"
#include "mempool.h"
#include "spell-slots.h"

union dngContext_Input {
	struct dngInput_Attack attack;
};

struct dngContext {
	struct dngIntBag * bag;
	struct dngCombat * combat;
	struct dngDicePool dices;
	struct dngEvent event;
	struct dngGrid grid;
	union dngContext_Input input;
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
