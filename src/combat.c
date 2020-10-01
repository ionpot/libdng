#include "combat.h"

#include "attr.h"
#include "entity.h"
#include "grid.h"
#include "int-bag.h"
#include "mempool.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define TURNS dngGrid_SLOTS

struct Turn {
	struct dngEntity * entity;
	int initiative;
	struct dngGrid_Position position;
};

struct dngCombat {
	struct dngIntBag * bag;
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

static const struct Turn *
getTurn(const T * self)
{
	assert(self);
	assert(self->turn >= 0);
	assert(self->turn < self->used);
	return self->turns + self->turn;
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
hasAlive(const T * self, enum dngGrid_SideId side)
{
	assert(self);
	for (int i = 0; i < self->used; i++) {
		const struct Turn * turn =
			self->turns + i;
		if (turn->position.side == side)
			if (dngEntity_isAlive(turn->entity))
				return true;
	}
	return false;
}

T *
dngCombat_create(struct dngMemPool * mem, struct dngIntBag * bag)
{
	assert(mem);
	assert(bag);
	T * self = dngMemPool_alloc(mem, sizeof(T));
	if (self) {
		self->bag = bag;
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
			.initiative = dngIntBag_next(self->bag),
			.position = pos
		};
	}
	self->round = 0;
	self->turn = self->used;
	qsort(self->turns, self->used, sizeof(struct Turn), cmpturns);
}

int
dngCombat_getRound(const T * self)
{
	assert(self);
	return self->round;
}

struct dngCombat_Turn
dngCombat_getTurn(const T * self)
{
	assert(self);
	const struct Turn * turn = getTurn(self);
	return (struct dngCombat_Turn){
		.entity = turn->entity,
		.position = turn->position
	};
}

bool
dngCombat_hasEnded(const T * self)
{
	assert(self);
	return !(
		hasAlive(self, dngGrid_SIDE_A)
		&&
		hasAlive(self, dngGrid_SIDE_B)
	);
}

bool
dngCombat_isEndOfRound(const T * self)
{
	assert(self);
	assert(self->turn <= self->used);
	return self->turn == self->used;
}

bool
dngCombat_isTurnOfSide(const T * self, enum dngGrid_SideId side)
{
	assert(self);
	return getTurn(self)->position.side == side;
}

void
dngCombat_nextRound(T * self)
{
	assert(self);
	assert(self->turn == self->used);
	self->round++;
}

void
dngCombat_nextTurn(T * self)
{
	assert(self);
	assert(self->turn <= self->used);
	int i = (self->turn == self->used) ? 0 : self->turn + 1;
	for (; i < self->used; i++) {
		const struct Turn * turn = self->turns + i;
		if (dngEntity_isAlive(turn->entity))
			break;
	}
	self->turn = i;
}
