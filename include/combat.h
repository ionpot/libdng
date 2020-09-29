#ifndef LIBDNG_COMBAT_H
#define LIBDNG_COMBAT_H

#include "entity.h"
#include "grid.h"
#include "mempool.h"

struct dngCombat_Turn {
	struct dngEntity * entity;
	struct dngGrid_Position position;
};

struct dngCombat;

struct dngCombat *
dngCombat_create(struct dngMemPool *);

void
dngCombat_init(struct dngCombat *, const struct dngGrid *);

struct dngCombat_Turn
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
