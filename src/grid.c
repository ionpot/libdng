#include "grid.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#define macro_switchLine(id, side)\
	switch (id) {\
	case dngGrid_LINE_BACK:\
		return &side->back;\
	case dngGrid_LINE_FRONT:\
		return &side->front;\
	default:\
			assert(false);\
	}

#define macro_switchSide(id, grid)\
	switch (id) {\
	case dngGrid_SIDE_A:\
		return &grid->side_a;\
	case dngGrid_SIDE_B:\
		return &grid->side_b;\
	default:\
			assert(false);\
	}

#define macro_switchSlot(id, line)\
	switch (id) {\
	case dngGrid_SLOT_1:\
		return &line->slot_1;\
	case dngGrid_SLOT_2:\
		return &line->slot_2;\
	case dngGrid_SLOT_3:\
		return &line->slot_3;\
	default:\
			assert(false);\
	}

static void
clearLine(struct dngGrid_Line * line)
{
	assert(line);
	line->slot_1 = NULL;
	line->slot_2 = NULL;
	line->slot_3 = NULL;
}

static struct dngGrid_Line *
getLine(
	struct dngGrid_Side * side,
	enum dngGrid_LineId line_id
) {
	assert(side);
	macro_switchLine(line_id, side)
}

static const struct dngGrid_Line *
getLine_const(
	const struct dngGrid_Side * side,
	enum dngGrid_LineId line_id
) {
	assert(side);
	macro_switchLine(line_id, side)
}

static struct dngGrid_Side *
getSide(
	struct dngGrid * grid,
	enum dngGrid_SideId side_id
) {
	assert(grid);
	macro_switchSide(side_id, grid) 
}

static const struct dngGrid_Side *
getSide_const(
	const struct dngGrid * grid,
	enum dngGrid_SideId side_id
) {
	assert(grid);
	macro_switchSide(side_id, grid) 
}

static struct dngEntity **
getSlot(
	struct dngGrid_Line * line,
	enum dngGrid_SlotId slot_id
) {
	assert(line);
	macro_switchSlot(slot_id, line)
}

static struct dngEntity * const *
getSlot_const(
	const struct dngGrid_Line * line,
	enum dngGrid_SlotId slot_id
) {
	assert(line);
	macro_switchSlot(slot_id, line)
}

static struct dngEntity **
grid2slot(
	struct dngGrid * grid,
	struct dngGrid_Position position
) {
	assert(grid);
	struct dngGrid_Side * side =
		getSide(grid, position.side);
	struct dngGrid_Line * line =
		getLine(side, position.line);
	return getSlot(line, position.slot);
}

static struct dngEntity * const *
grid2slot_const(
	const struct dngGrid * grid,
	struct dngGrid_Position position
) {
	assert(grid);
	const struct dngGrid_Side * side =
		getSide_const(grid, position.side);
	const struct dngGrid_Line * line =
		getLine_const(side, position.line);
	return getSlot_const(line, position.slot);
}

static bool
line2bool(
	const struct dngGrid_Line * line,
	enum dngGrid_SlotId slot_id
) {
	assert(line);
	struct dngEntity * const * slot =
		getSlot_const(line, slot_id);
	return *slot != NULL;
}

static bool
canReachSameLine(
	const struct dngGrid_Line * line,
	const struct dngGrid_Position * s_pos,
	const struct dngGrid_Position * t_pos
) {
	assert(line);
	assert(s_pos);
	assert(t_pos);
	assert(s_pos->side == t_pos->side);
	assert(s_pos->line == t_pos->line);

	if (s_pos->slot == dngGrid_SLOT_2)
		return true;

	if (t_pos->slot == dngGrid_SLOT_2)
		return true;

	return line->slot_2 == NULL;
}

static bool
canReachLine(
	const struct dngGrid_Line * t_line,
	const struct dngGrid_Position * s_pos,
	const struct dngGrid_Position * t_pos
) {
	assert(t_line);
	assert(s_pos);
	assert(t_pos);
	assert(!(s_pos->side == t_pos->side
				&& s_pos->line == t_pos->line));

	if (s_pos->slot == dngGrid_SLOT_2)
		return true;

	if (t_pos->slot == dngGrid_SLOT_2)
		return true;

	if (s_pos->slot == t_pos->slot)
		return true;

	if (!line2bool(t_line, s_pos->slot))
		if (!t_line->slot_2)
			return true;

	return false;
}

static bool
hasEntity(struct dngGrid_Line line)
{
	return (line.slot_1 != NULL)
		|| (line.slot_2 != NULL)
		|| (line.slot_3 != NULL);
}

bool
dngGrid_canReach(
	const struct dngGrid * grid,
	const struct dngGrid_Position * s_pos,
	const struct dngGrid_Position * t_pos
) {
	assert(grid);
	assert(s_pos);
	assert(t_pos);

	const struct dngGrid_Side * s_side =
		getSide_const(grid, s_pos->side);

	const struct dngGrid_Line * s_line =
		getLine_const(s_side, s_pos->line);

	if (s_pos->side == t_pos->side) {
		if (s_pos->line == t_pos->line) {
			return canReachSameLine(s_line, s_pos, t_pos);
		}
		const struct dngGrid_Line * t_line =
			getLine_const(s_side, t_pos->line);

		return canReachLine(t_line, s_pos, t_pos);
	}

	const struct dngGrid_Side * t_side =
		getSide_const(grid, t_pos->side);

	const struct dngGrid_Line * t_line =
		getLine_const(t_side, t_pos->line);

	if (s_pos->line == dngGrid_LINE_FRONT) {
		if (t_pos->line == dngGrid_LINE_BACK) {
			if (hasEntity(t_side->front))
				return false;
		}
		return canReachLine(t_line, s_pos, t_pos);
	}

	if (hasEntity(s_side->front))
		return false;

	if (t_pos->line == dngGrid_LINE_BACK) {
		if (hasEntity(t_side->front))
			return false;
	}

	return canReachLine(t_line, s_pos, t_pos);
}

void
dngGrid_clear(struct dngGrid * grid)
{
	assert(grid);
	dngGrid_clearSide(&grid->side_a);
	dngGrid_clearSide(&grid->side_b);
}

void
dngGrid_clearSide(struct dngGrid_Side * side)
{
	assert(side);
	clearLine(&side->front);
	clearLine(&side->back);
}

struct dngEntity *
dngGrid_getEntity(
	const struct dngGrid * grid,
	struct dngGrid_Position position
) {
	assert(grid);
	return *grid2slot_const(grid, position);
}

void
dngGrid_putEntity(
	struct dngGrid * grid,
	struct dngGrid_Position position,
	struct dngEntity * entity
) {
	assert(grid);
	struct dngEntity ** slot =
		grid2slot(grid, position);
	*slot = entity;
}