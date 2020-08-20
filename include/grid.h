#ifndef LIBDNG_GRID_H
#define LIBDNG_GRID_H

#include "entity.h"

#include <stdbool.h>

#define dngGrid_SLOTS 12

/*  ________________________ ________________________
 * |                        |                        |
 * |         Side A         |         Side B         |
 * |________________________|________________________|
 * |           |            |            |           |
 * | Back Line | Front Line | Front Line | Back Line |
 * |___________|____________|____________|___________|
 * |           |            |            |           |
 * |   Slot 1  |   Slot 1   |   Slot 1   |  Slot 1   |
 * |   Slot 2  |   Slot 2   |   Slot 2   |  Slot 2   |
 * |   Slot 3  |   Slot 3   |   Slot 3   |  Slot 3   |
 * |___________|____________|____________|___________|
 */

enum dngGrid_LineId {
	dngGrid_LINE_FRONT,
	dngGrid_LINE_BACK
};

enum dngGrid_SideId {
	dngGrid_SIDE_A,
	dngGrid_SIDE_B
};

enum dngGrid_SlotId {
	dngGrid_SLOT_1,
	dngGrid_SLOT_2,
	dngGrid_SLOT_3
};

struct dngGrid_Line {
	struct dngEntity * slot_1;
	struct dngEntity * slot_2;
	struct dngEntity * slot_3;
};

struct dngGrid_Position {
	enum dngGrid_LineId line;
	enum dngGrid_SideId side;
	enum dngGrid_SlotId slot;
};

struct dngGrid_Side {
	struct dngGrid_Line back;
	struct dngGrid_Line front;
};

struct dngGrid {
	struct dngGrid_Side side_a;
	struct dngGrid_Side side_b;
};

bool
dngGrid_canReach(
	const struct dngGrid *,
	const struct dngGrid_Position * source,
	const struct dngGrid_Position * target
);

void
dngGrid_clear(struct dngGrid *);

void
dngGrid_clearSide(struct dngGrid_Side *);

struct dngEntity *
dngGrid_getEntity(
	const struct dngGrid *,
	struct dngGrid_Position
);

void
dngGrid_putEntity(
	struct dngGrid *,
	struct dngGrid_Position,
	struct dngEntity *
);

#endif
