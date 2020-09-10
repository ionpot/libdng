#ifndef LIBDNG_COMBAT_H
#define LIBDNG_COMBAT_H

#include "entity.h"
#include "grid.h"

#include <stdbool.h>

struct dngCombat_Turn {
	struct dngEntity * entity;
	struct dngGrid_Position position;
};

struct dngCombat {
	int round;
	struct dngCombat_Turn turns[dngGrid_SLOTS];
	int turn_index;
	int used;
};

struct dngCombat
dngCombat_fromGrid(struct dngGrid);

bool
dngCombat_nextRound(struct dngCombat *);

const struct dngCombat_Turn *
dngCombat_nextTurn(struct dngCombat *);

#endif
