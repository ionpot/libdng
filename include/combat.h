#ifndef LIBDNG_COMBAT_H
#define LIBDNG_COMBAT_H

#include "entity.h"
#include "grid.h"
#include "mempool.h"

struct dngCombat_Turn {
	struct dngEntity * entity;
	struct dngGrid_Position position;
	int round;
};

struct dngCombat;

struct dngCombat *
dngCombat_create(struct dngMemPool *);

void
dngCombat_init(struct dngCombat *, const struct dngGrid *);

const struct dngCombat_Turn *
dngCombat_nextTurn(struct dngCombat *);

#endif
