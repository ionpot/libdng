#include "combat.h"

#include "attr.h"
#include "entity.h"
#include "grid.h"
#include "int-bag.h"
#include "mempool.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define TURNS dngGrid_SLOTS

struct Turn {
	struct dngEntity * entity;
	int initiative;
	struct dngGrid_Position position;
};

struct dngCombat {
	int round;
	int turn;
	struct Turn turns[TURNS];
	int used;
};

typedef struct dngCombat T;

static int
getInitiative(const struct dngEntity * entity)
{
	assert(entity);
	struct dngAttr attr = dngEntity_getInitiative(entity);
	return dngAttr_getTotal(&attr);
}

static int
cmpturns(const void * arg_a, const void * arg_b)
{
	const struct Turn * turn_a = arg_a;
	const struct Turn * turn_b = arg_b;
	int a = getInitiative(turn_a->entity);
	int b = getInitiative(turn_b->entity);
	if (a == b) {
		a = turn_a->initiative;
		b = turn_b->initiative;
	}
	return a - b;
}

static bool
checkSides(const T * self)
{
	assert(self);
	bool side_a = false;
	bool side_b = false;
	for (int i = 0; i < self->used; i++) {
		const struct Turn * turn =
			self->turns + i;
		bool alive = dngEntity_isAlive(turn->entity);
		if (turn->position.side == dngGrid_SIDE_A)
			side_a |= alive;
		else if (turn->position.side == dngGrid_SIDE_B)
			side_b |= alive;
		else
			assert(false);
		if (side_a && side_b)
			return true;
	}
	return false;
}

static const struct dngCombat_Turn *
nextTurn(T * self)
{
	assert(self);
	assert(self->used > 0);
	if (self->turn < self->used) {
		self->turn++;
	} else {
		self->round++;
		self->turn = 0;
	}
	static struct dngCombat_Turn turn;
	const struct Turn * t =
		self->turns + self->turn;
	if (dngEntity_isAlive(t->entity)) {
		turn.entity = t->entity;
		turn.position = t->position;
		turn.round = self->round;
		return &turn;
	}
	return nextTurn(self);
}

T *
dngCombat_create(struct dngMemPool * mem)
{
	assert(mem);
	T * self = dngMemPool_alloc(mem, sizeof(T));
	if (self) {
		self->round = 0;
		self->turn = 0;
		self->used = 0;
	}
	return self;
}

void
dngCombat_init(T * self, const struct dngGrid * grid)
{
	assert(self);
	assert(grid);
	self->used = 0;
	for (int i = 0; i < TURNS; i++) {
		struct dngGrid_Position pos =
			dngGrid_positions[i];
		struct dngEntity * entity =
			dngGrid_getEntity(grid, pos);
		if (!entity)
			continue;
		self->turns[self->used++] = (struct Turn){
			.entity = entity,
			.initiative = dngIntBag_next(),
			.position = pos
		};
	}
	self->round = 0;
	self->turn = self->used;
	qsort(self->turns, self->used, sizeof(struct Turn), cmpturns);
}

const struct dngCombat_Turn *
dngCombat_nextTurn(T * self)
{
	assert(self);
	return checkSides(self)
		? nextTurn(self)
		: NULL;
}
