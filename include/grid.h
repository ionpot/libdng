#ifndef LIBDNG_GRID_H
#define LIBDNG_GRID_H

#include "entity.h"

#include <stdbool.h>

#define DNG_GRID_SLOTS 12

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

enum DNG_Grid_LineId {
	DNG_GRID_LINE_FRONT,
	DNG_GRID_LINE_BACK
};

enum DNG_Grid_SideId {
	DNG_GRID_SIDE_A,
	DNG_GRID_SIDE_B
};

enum DNG_Grid_SlotId {
	DNG_GRID_SLOT_1,
	DNG_GRID_SLOT_2,
	DNG_GRID_SLOT_3
};

struct DNG_Grid_Line {
	struct DNG_Entity * slot_1;
	struct DNG_Entity * slot_2;
	struct DNG_Entity * slot_3;
};

struct DNG_Grid_Position {
	enum DNG_Grid_LineId line;
	enum DNG_Grid_SideId side;
	enum DNG_Grid_SlotId slot;
};

struct DNG_Grid_Side {
	struct DNG_Grid_Line back;
	struct DNG_Grid_Line front;
};

struct DNG_Grid {
	struct DNG_Grid_Side side_a;
	struct DNG_Grid_Side side_b;
};

bool
DNG_Grid_canReach(
	const struct DNG_Grid *,
	const struct DNG_Grid_Position * source,
	const struct DNG_Grid_Position * target
);

void
DNG_Grid_clear(struct DNG_Grid *);

void
DNG_Grid_clearSide(struct DNG_Grid_Side *);

struct DNG_Entity *
DNG_Grid_getEntity(
	const struct DNG_Grid *,
	struct DNG_Grid_Position
);

void
DNG_Grid_putEntity(
	struct DNG_Grid *,
	struct DNG_Grid_Position,
	struct DNG_Entity *
);

#endif
