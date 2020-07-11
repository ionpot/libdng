#ifndef LIBDNG_GRID_H
#define LIBDNG_GRID_H

#include "entity.h"

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

enum DNG_Grid_Line_Id {
	DNG_GRIDLINE_FRONT,
	DNG_GRIDLINE_BACK
};

enum DNG_Grid_Side_Id {
	DNG_GRIDSIDE_A,
	DNG_GRIDSIDE_B
};

enum DNG_Grid_Slot_Id {
	DNG_GRIDSLOT_1,
	DNG_GRIDSLOT_2,
	DNG_GRIDSLOT_3
};

struct DNG_Grid_Line {
	struct DNG_Entity * slot_1;
	struct DNG_Entity * slot_2;
	struct DNG_Entity * slot_3;
};

struct DNG_Grid_Position {
	enum DNG_Grid_Line_Id line;
	enum DNG_Grid_Side_Id side;
	enum DNG_Grid_Slot_Id slot;
};

struct DNG_Grid_Side {
	struct DNG_Grid_Line back;
	struct DNG_Grid_Line front;
};

struct DNG_Grid {
	struct DNG_Grid_Side side_a;
	struct DNG_Grid_Side side_b;
};

void
DNG_Grid_clear(struct DNG_Grid *);

void
DNG_Grid_clearLine(struct DNG_Grid_Line *);

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
