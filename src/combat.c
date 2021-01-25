#include "combat.h"

#include "attr.h"
#include "entity.h"
#include "grid.h"
#include "grid-slot.h"
#include "int-bag.h"
#include "mempool.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define TURNS dngGrid_SLOTS

struct Turn {
	int initiative;
	struct dngGridSlot slot;
};

struct dngCombat {
	struct dngIntBag * bag;
	const struct dngGrid * grid;
	int round;
	int turn;
	struct Turn turns[TURNS];
	int used;
};

typedef struct dngCombat T;

static int
getIndexOfEntity(const T * self, const struct dngEntity * entity)
{
	assert(self);
	assert(entity);
	assert(self->used <= TURNS);
	for (int i = 0; i < self->used; i++) {
		if (self->turns[i].slot.entity == entity)
			return i;
	}
	return -1;
}

static int
getInitiative(const struct dngEntity * entity)
{
	assert(entity);
	struct dngAttr attr = dngEntity_getInitiative(entity);
	return dngAttr_getTotal(attr);
}

static const struct Turn *
getTurnAt(const T * self, int i)
{
	assert(self);
	assert(i >= 0);
	assert(i < self->used);
	return self->turns + i;
}

static struct dngGridSlot
getSlotAt(const T * self, int i)
{
	assert(self);
	return getTurnAt(self, i)->slot;
}

static const struct Turn *
getTurn(const T * self)
{
	assert(self);
	return getTurnAt(self, self->turn);
}

static struct dngGridSlot
getSlot(const T * self)
{
	assert(self);
	return getTurn(self)->slot;
}

static int
cmpturns(const void * arg_a, const void * arg_b)
{
	const struct Turn * turn_a = arg_a;
	const struct Turn * turn_b = arg_b;
	int a = getInitiative(turn_a->slot.entity);
	int b = getInitiative(turn_b->slot.entity);
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
	assert(self->used <= TURNS);
	for (int i = 0; i < self->used; i++) {
		struct dngGridSlot slot = getSlotAt(self, i);
		if (slot.position.side == side)
			if (dngEntity_isAlive(slot.entity))
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
		self->grid = NULL;
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
	self->grid = grid;
	self->used = 0;
	for (int i = 0; i < TURNS; i++) {
		struct dngGridSlot slot =
			dngGridSlot_fromPosition(grid, dngGrid_positions[i]);
		if (!slot.entity)
			continue;
		self->turns[self->used++] = (struct Turn){
			.initiative = dngIntBag_next(self->bag),
			.slot = slot
		};
	}
	self->round = 0;
	self->turn = self->used;
	qsort(self->turns, self->used, sizeof(struct Turn), cmpturns);
}

struct dngEntity *
dngCombat_findFirstReachable(const T * self, struct dngGridSlot source)
{
	assert(self);
	assert(self->grid);
	assert(self->used > 0);
	assert(self->used <= TURNS);
	int offset = getIndexOfEntity(self, source.entity);
	assert(offset >= 0);
	int count = self->used - 1;
	for (int i = 1; i < count; i++) {
		struct dngGridSlot target
			= getSlotAt(self, (offset + i) % self->used);
		if (target.position.side == source.position.side)
			continue;
		if (dngGrid_canReach(self->grid, source.position, target.position))
			return target.entity;
	}
	return NULL;
}

int
dngCombat_getRound(const T * self)
{
	assert(self);
	return self->round;
}

struct dngGridSlot
dngCombat_getTurn(const T * self)
{
	assert(self);
	return getSlot(self);
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
	return getSlot(self).position.side == side;
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
	assert(self->used <= TURNS);
	for (int i = 1; i < self->used; i++) {
		int index = (self->turn + i) % self->used;
		struct dngGridSlot slot = getSlotAt(self, index);
		if (dngEntity_isAlive(slot.entity)) {
			self->turn = index;
			return;
		}
	}
	assert(false);
}
