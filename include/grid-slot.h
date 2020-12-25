#ifndef LIBDNG_GRID_SLOT_H
#define LIBDNG_GRID_SLOT_H

#include "entity.h"
#include "grid.h"

struct dngGridSlot {
	struct dngEntity * entity;
	struct dngGrid_Position position;
};

struct dngGridSlot
dngGridSlot_fromPosition(const struct dngGrid *, struct dngGrid_Position);

#endif
