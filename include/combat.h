#ifndef LIBDNG_COMBAT_H
#define LIBDNG_COMBAT_H

#include "entity.h"
#include "grid.h"
#include "grid-slot.h"
#include "int-bag.h"
#include "mempool.h"

struct dngCombat;

struct dngCombat *
dngCombat_create(struct dngMemPool *, struct dngIntBag *);

void
dngCombat_init(struct dngCombat *, const struct dngGrid *);

struct dngEntity *
dngCombat_findFirstReachable(const struct dngCombat *, struct dngGridSlot);

int
dngCombat_getRound(const struct dngCombat *);

struct dngGridSlot
dngCombat_getTurn(const struct dngCombat *);

bool
dngCombat_hasEnded(const struct dngCombat *);

bool
dngCombat_isEndOfRound(const struct dngCombat *);

bool
dngCombat_isTurnOfSide(const struct dngCombat *, enum dngGrid_SideId);

void
dngCombat_nextRound(struct dngCombat *);

void
dngCombat_nextTurn(struct dngCombat *);

#endif
