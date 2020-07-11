#ifndef LIBDNG_COMBAT_H
#define LIBDNG_COMBAT_H

#include "entity.h"
#include "grid.h"

#include <stdbool.h>

struct DNG_Combat_Turn {
	struct DNG_Entity * entity;
	struct DNG_Grid_Position position;
};

struct DNG_Combat {
	int round;
	int turn_index;
	int used;
	struct DNG_Combat_Turn turns[DNG_GRID_SLOTS];
};

struct DNG_Combat
DNG_Combat_fromGrid(struct DNG_Grid);

bool
DNG_Combat_nextRound(struct DNG_Combat *);

const struct DNG_Combat_Turn *
DNG_Combat_nextTurn(struct DNG_Combat *);

#endif
