#ifndef LIBDNG_CONTEXT_H
#define LIBDNG_CONTEXT_H

#include "combat.h"
#include "dice-pool.h"
#include "entities.h"
#include "grid.h"
#include "int-bag.h"
#include "mempool.h"
#include "spell-slots.h"
#include "status.h"
#include "steps.h"

#include <stdbool.h>

struct dngContext {
	struct dngIntBag * bag;
	struct dngCombat * combat;
	struct dngDicePool dice;
	struct dngEntities entities;
	struct dngGrid grid;
	struct dngMemPool * mempool;
	struct dngSpellSlots slots;
	enum dngStatus status;
	struct dngSteps steps;
};

struct dngContext *
dngContext_create(void);

void
dngContext_destroy(struct dngContext *);

bool
dngContext_isOk(const struct dngContext *);

void
dngContext_reset(struct dngContext *);

void
dngContext_setNoMem(struct dngContext *);

#endif
