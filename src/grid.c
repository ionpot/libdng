#include "grid.h"

#include "entity.h"
#include "entities.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#define macro_switchLine(id, side)\
	switch (id) {\
	case dngGrid_LINE_BACK:\
		return &side->back;\
	case dngGrid_LINE_FRONT:\
		return &side->front;\
	}

#define macro_switchSide(id, grid)\
	switch (id) {\
	case dngGrid_SIDE_A:\
		return &grid->side_a;\
	case dngGrid_SIDE_B:\
		return &grid->side_b;\
	}

#define macro_switchSlot(id, line)\
	switch (id) {\
	case dngGrid_SLOT_1:\
		return &line->slot_1;\
	case dngGrid_SLOT_2:\
		return &line->slot_2;\
	case dngGrid_SLOT_3:\
		return &line->slot_3;\
	}

typedef struct dngGrid T;

const struct dngGrid_Position
dngGrid_positions[dngGrid_SLOTS] = {
	{ 	.side = dngGrid_SIDE_A,
		.line = dngGrid_LINE_FRONT,
		.slot = dngGrid_SLOT_1
	},
	{ 	.side = dngGrid_SIDE_A,
		.line = dngGrid_LINE_FRONT,
		.slot = dngGrid_SLOT_2
	},
	{ 	.side = dngGrid_SIDE_A,
		.line = dngGrid_LINE_FRONT,
		.slot = dngGrid_SLOT_3
	},
	{ 	.side = dngGrid_SIDE_A,
		.line = dngGrid_LINE_BACK,
		.slot = dngGrid_SLOT_1
	},
	{ 	.side = dngGrid_SIDE_A,
		.line = dngGrid_LINE_BACK,
		.slot = dngGrid_SLOT_2
	},
	{ 	.side = dngGrid_SIDE_A,
		.line = dngGrid_LINE_BACK,
		.slot = dngGrid_SLOT_3
	},
	{ 	.side = dngGrid_SIDE_B,
		.line = dngGrid_LINE_FRONT,
		.slot = dngGrid_SLOT_1
	},
	{ 	.side = dngGrid_SIDE_B,
		.line = dngGrid_LINE_FRONT,
		.slot = dngGrid_SLOT_2
	},
	{ 	.side = dngGrid_SIDE_B,
		.line = dngGrid_LINE_FRONT,
		.slot = dngGrid_SLOT_3
	},
	{ 	.side = dngGrid_SIDE_B,
		.line = dngGrid_LINE_BACK,
		.slot = dngGrid_SLOT_1
	},
	{ 	.side = dngGrid_SIDE_B,
		.line = dngGrid_LINE_BACK,
		.slot = dngGrid_SLOT_2
	},
	{ 	.side = dngGrid_SIDE_B,
		.line = dngGrid_LINE_BACK,
		.slot = dngGrid_SLOT_3
	}
};

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
	assert(false);
}

static const struct dngGrid_Line *
getLine_const(
	const struct dngGrid_Side * side,
	enum dngGrid_LineId line_id
) {
	assert(side);
	macro_switchLine(line_id, side)
	assert(false);
}

static struct dngGrid_Side *
getSide(T * self, enum dngGrid_SideId side_id)
{
	assert(self);
	macro_switchSide(side_id, self) 
	assert(false);
}

static const struct dngGrid_Side *
getSide_const(const T * self, enum dngGrid_SideId side_id)
{
	assert(self);
	macro_switchSide(side_id, self) 
	assert(false);
}

static struct dngEntity **
getSlot(
	struct dngGrid_Line * line,
	enum dngGrid_SlotId slot_id
) {
	assert(line);
	macro_switchSlot(slot_id, line)
	assert(false);
}

static struct dngEntity * const *
getSlot_const(
	const struct dngGrid_Line * line,
	enum dngGrid_SlotId slot_id
) {
	assert(line);
	macro_switchSlot(slot_id, line)
	assert(false);
}

static struct dngEntity **
grid2slot(T * self, struct dngGrid_Position position)
{
	assert(self);
	struct dngGrid_Side * side =
		getSide(self, position.side);
	struct dngGrid_Line * line =
		getLine(side, position.line);
	return getSlot(line, position.slot);
}

static struct dngEntity * const *
grid2slot_const(const T * self, struct dngGrid_Position position)
{
	assert(self);
	const struct dngGrid_Side * side =
		getSide_const(self, position.side);
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
	struct dngGrid_Position s_pos,
	struct dngGrid_Position t_pos
) {
	assert(line);
	assert(s_pos.side == t_pos.side);
	assert(s_pos.line == t_pos.line);

	if (s_pos.slot == dngGrid_SLOT_2)
		return true;

	if (t_pos.slot == dngGrid_SLOT_2)
		return true;

	return line->slot_2 == NULL;
}

static bool
canReachLine(
	const struct dngGrid_Line * t_line,
	struct dngGrid_Position s_pos,
	struct dngGrid_Position t_pos
) {
	assert(t_line);
	assert(!(s_pos.side == t_pos.side
				&& s_pos.line == t_pos.line));

	if (s_pos.slot == dngGrid_SLOT_2)
		return true;

	if (t_pos.slot == dngGrid_SLOT_2)
		return true;

	if (s_pos.slot == t_pos.slot)
		return true;

	if (!line2bool(t_line, s_pos.slot))
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

static void
resetLine(struct dngGrid_Line * line, struct dngEntities entities)
{
	assert(line);
	if (line->slot_1)
		dngEntities_return(entities, line->slot_1);
	if (line->slot_2)
		dngEntities_return(entities, line->slot_2);
	if (line->slot_3)
		dngEntities_return(entities, line->slot_3);
}

bool
dngGrid_canReach(
	const T * self,
	struct dngGrid_Position s_pos,
	struct dngGrid_Position t_pos
) {
	assert(self);

	const struct dngGrid_Side * s_side =
		getSide_const(self, s_pos.side);

	const struct dngGrid_Line * s_line =
		getLine_const(s_side, s_pos.line);

	if (s_pos.side == t_pos.side) {
		if (s_pos.line == t_pos.line) {
			return canReachSameLine(s_line, s_pos, t_pos);
		}
		const struct dngGrid_Line * t_line =
			getLine_const(s_side, t_pos.line);

		return canReachLine(t_line, s_pos, t_pos);
	}

	const struct dngGrid_Side * t_side =
		getSide_const(self, t_pos.side);

	const struct dngGrid_Line * t_line =
		getLine_const(t_side, t_pos.line);

	if (s_pos.line == dngGrid_LINE_FRONT) {
		if (t_pos.line == dngGrid_LINE_BACK) {
			if (hasEntity(t_side->front))
				return false;
		}
		return canReachLine(t_line, s_pos, t_pos);
	}

	if (hasEntity(s_side->front))
		return false;

	if (t_pos.line == dngGrid_LINE_BACK) {
		if (hasEntity(t_side->front))
			return false;
	}

	return canReachLine(t_line, s_pos, t_pos);
}

void
dngGrid_clear(T * self)
{
	assert(self);
	dngGrid_clearSide(&self->side_a);
	dngGrid_clearSide(&self->side_b);
}

void
dngGrid_clearSide(struct dngGrid_Side * side)
{
	assert(side);
	clearLine(&side->front);
	clearLine(&side->back);
}

struct dngEntity *
dngGrid_getEntity(const T * self, struct dngGrid_Position position)
{
	assert(self);
	return *grid2slot_const(self, position);
}

void
dngGrid_putEntity(
	T * self,
	struct dngGrid_Position position,
	struct dngEntity * entity
) {
	assert(self);
	struct dngEntity ** slot =
		grid2slot(self, position);
	*slot = entity;
}

void
dngGrid_resetSide(struct dngGrid_Side * side, struct dngEntities entities)
{
	assert(side);
	resetLine(&side->front, entities);
	resetLine(&side->back, entities);
	dngGrid_clearSide(side);
}
