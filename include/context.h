#ifndef LIBDNG_CONTEXT_H
#define LIBDNG_CONTEXT_H

#include "combat.h"
#include "dice-pool.h"
#include "entities.h"
#include "event-list.h"
#include "grid.h"
#include "input-def.h"
#include "int-bag.h"
#include "mempool.h"
#include "spell-slots.h"
#include "status.h"

union dngContext_Input {
	struct dngInput_Attack attack;
};

struct dngContext {
	struct dngIntBag * bag;
	struct dngCombat * combat;
	struct dngDicePool dices;
	struct dngEntities entities;
	struct dngEventList events;
	struct dngGrid grid;
	union dngContext_Input input;
	struct dngMemPool * mempool;
	struct dngSpellSlots slots;
	enum dngStatus status;
};

struct dngContext *
dngContext_create(void);

void
dngContext_destroy(struct dngContext *);

void
dngContext_reset(struct dngContext *);

void
dngContext_setNoMem(struct dngContext *);

#endif
