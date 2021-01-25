#ifndef LIBDNG_CONTEXT_H
#define LIBDNG_CONTEXT_H

#include "combat.h"
#include "combat-action.h"
#include "dice-pool.h"
#include "entities.h"
#include "grid.h"
#include "int-bag.h"
#include "mempool.h"
#include "spell-slots.h"
#include "status.h"
#include "steps.h"

union dngContext_Input {
	struct dngCombatAction action;
};

struct dngContext {
	struct dngIntBag * bag;
	struct dngCombat * combat;
	struct dngDicePool dice;
	struct dngEntities entities;
	struct dngGrid grid;
	union dngContext_Input input;
	struct dngMemPool * mempool;
	struct dngSpellSlots slots;
	enum dngStatus status;
	struct dngSteps steps;
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
