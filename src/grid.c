#include "grid.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#define macro_switchLine(id, side)\
	switch (id) {\
	case DNG_GRID_LINE_BACK:\
		return &side->back;\
	case DNG_GRID_LINE_FRONT:\
		return &side->front;\
	default:\
			assert(false);\
	}

#define macro_switchSide(id, grid)\
	switch (id) {\
	case DNG_GRID_SIDE_A:\
		return &grid->side_a;\
	case DNG_GRID_SIDE_B:\
		return &grid->side_b;\
	default:\
			assert(false);\
	}

#define macro_switchSlot(id, line)\
	switch (id) {\
	case DNG_GRID_SLOT_1:\
		return &line->slot_1;\
	case DNG_GRID_SLOT_2:\
		return &line->slot_2;\
	case DNG_GRID_SLOT_3:\
		return &line->slot_3;\
	default:\
			assert(false);\
	}

static void
clearLine(struct DNG_Grid_Line * line)
{
	assert(line);
	line->slot_1 = NULL;
	line->slot_2 = NULL;
	line->slot_3 = NULL;
}

static struct DNG_Grid_Line *
getLine(
	struct DNG_Grid_Side * side,
	enum DNG_Grid_LineId line_id
) {
	assert(side);
	macro_switchLine(line_id, side)
}

static const struct DNG_Grid_Line *
getLine_const(
	const struct DNG_Grid_Side * side,
	enum DNG_Grid_LineId line_id
) {
	assert(side);
	macro_switchLine(line_id, side)
}

static struct DNG_Grid_Side *
getSide(
	struct DNG_Grid * grid,
	enum DNG_Grid_SideId side_id
) {
	assert(grid);
	macro_switchSide(side_id, grid) 
}

static const struct DNG_Grid_Side *
getSide_const(
	const struct DNG_Grid * grid,
	enum DNG_Grid_SideId side_id
) {
	assert(grid);
	macro_switchSide(side_id, grid) 
}

static struct DNG_Entity **
getSlot(
	struct DNG_Grid_Line * line,
	enum DNG_Grid_SlotId slot_id
) {
	assert(line);
	macro_switchSlot(slot_id, line)
}

static struct DNG_Entity * const *
getSlot_const(
	const struct DNG_Grid_Line * line,
	enum DNG_Grid_SlotId slot_id
) {
	assert(line);
	macro_switchSlot(slot_id, line)
}

static struct DNG_Entity **
grid2slot(
	struct DNG_Grid * grid,
	struct DNG_Grid_Position position
) {
	assert(grid);
	struct DNG_Grid_Side * side =
		getSide(grid, position.side);
	struct DNG_Grid_Line * line =
		getLine(side, position.line);
	return getSlot(line, position.slot);
}

static struct DNG_Entity * const *
grid2slot_const(
	const struct DNG_Grid * grid,
	struct DNG_Grid_Position position
) {
	assert(grid);
	const struct DNG_Grid_Side * side =
		getSide_const(grid, position.side);
	const struct DNG_Grid_Line * line =
		getLine_const(side, position.line);
	return getSlot_const(line, position.slot);
}

static bool
line2bool(
	const struct DNG_Grid_Line * line,
	enum DNG_Grid_SlotId slot_id
) {
	assert(line);
	struct DNG_Entity * const * slot =
		getSlot_const(line, slot_id);
	return *slot != NULL;
}

static bool
canReachSameLine(
	const struct DNG_Grid_Line * line,
	const struct DNG_Grid_Position * s_pos,
	const struct DNG_Grid_Position * t_pos
) {
	assert(line);
	assert(s_pos);
	assert(t_pos);
	assert(s_pos->side == t_pos->side);
	assert(s_pos->line == t_pos->line);

	if (s_pos->slot == DNG_GRID_SLOT_2)
		return true;

	if (t_pos->slot == DNG_GRID_SLOT_2)
		return true;

	return line->slot_2 == NULL;
}

static bool
canReachLine(
	const struct DNG_Grid_Line * t_line,
	const struct DNG_Grid_Position * s_pos,
	const struct DNG_Grid_Position * t_pos
) {
	assert(t_line);
	assert(s_pos);
	assert(t_pos);
	assert(!(s_pos->side == t_pos->side
				&& s_pos->line == t_pos->line));

	if (s_pos->slot == DNG_GRID_SLOT_2)
		return true;

	if (t_pos->slot == DNG_GRID_SLOT_2)
		return true;

	if (s_pos->slot == t_pos->slot)
		return true;

	if (!line2bool(t_line, s_pos->slot))
		if (!t_line->slot_2)
			return true;

	return false;
}

static bool
hasEntity(struct DNG_Grid_Line line)
{
	return (line.slot_1 != NULL)
		|| (line.slot_2 != NULL)
		|| (line.slot_3 != NULL);
}

bool
DNG_Grid_canReach(
	const struct DNG_Grid * grid,
	const struct DNG_Grid_Position * s_pos,
	const struct DNG_Grid_Position * t_pos
) {
	assert(grid);
	assert(s_pos);
	assert(t_pos);

	const struct DNG_Grid_Side * s_side =
		getSide_const(grid, s_pos->side);

	const struct DNG_Grid_Line * s_line =
		getLine_const(s_side, s_pos->line);

	if (s_pos->side == t_pos->side) {
		if (s_pos->line == t_pos->line) {
			return canReachSameLine(s_line, s_pos, t_pos);
		}
		const struct DNG_Grid_Line * t_line =
			getLine_const(s_side, t_pos->line);

		return canReachLine(t_line, s_pos, t_pos);
	}

	const struct DNG_Grid_Side * t_side =
		getSide_const(grid, t_pos->side);

	const struct DNG_Grid_Line * t_line =
		getLine_const(t_side, t_pos->line);

	if (s_pos->line == DNG_GRID_LINE_FRONT) {
		if (t_pos->line == DNG_GRID_LINE_BACK) {
			if (hasEntity(t_side->front))
				return false;
		}
		return canReachLine(t_line, s_pos, t_pos);
	}

	if (hasEntity(s_side->front))
		return false;

	if (t_pos->line == DNG_GRID_LINE_BACK) {
		if (hasEntity(t_side->front))
			return false;
	}

	return canReachLine(t_line, s_pos, t_pos);
}

void
DNG_Grid_clear(struct DNG_Grid * grid)
{
	assert(grid);
	DNG_Grid_clearSide(&grid->side_a);
	DNG_Grid_clearSide(&grid->side_b);
}

void
DNG_Grid_clearSide(struct DNG_Grid_Side * side)
{
	assert(side);
	clearLine(&side->front);
	clearLine(&side->back);
}

struct DNG_Entity *
DNG_Grid_getEntity(
	const struct DNG_Grid * grid,
	struct DNG_Grid_Position position
) {
	assert(grid);
	return *grid2slot_const(grid, position);
}

void
DNG_Grid_putEntity(
	struct DNG_Grid * grid,
	struct DNG_Grid_Position position,
	struct DNG_Entity * entity
) {
	assert(grid);
	struct DNG_Entity ** slot =
		grid2slot(grid, position);
	*slot = entity;
}
