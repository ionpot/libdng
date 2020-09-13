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
checkSides(const struct dngCombat * combat)
{
	assert(combat);
	bool side_a = false;
	bool side_b = false;
	for (int i = 0; i < combat->used; i++) {
		const struct Turn * turn =
			combat->turns + i;
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
nextTurn(struct dngCombat * combat)
{
	assert(combat);
	assert(combat->used > 0);
	if (combat->turn < combat->used) {
		combat->turn++;
	} else {
		combat->round++;
		combat->turn = 0;
	}
	static struct dngCombat_Turn turn;
	const struct Turn * t =
		combat->turns + combat->turn;
	if (dngEntity_isAlive(t->entity)) {
		turn.entity = t->entity;
		turn.position = t->position;
		turn.round = combat->round;
		return &turn;
	}
	return nextTurn(combat);
}

struct dngCombat *
dngCombat_create(struct dngMemPool * mem)
{
	assert(mem);
	struct dngCombat * combat =
		dngMemPool_alloc(mem, sizeof(struct dngCombat));
	if (combat) {
		combat->round = 0;
		combat->turn = 0;
		combat->used = 0;
	}
	return combat;
}

void
dngCombat_init(struct dngCombat * combat, const struct dngGrid * grid)
{
	assert(combat);
	assert(grid);
	combat->used = 0;
	for (int i = 0; i < TURNS; i++) {
		struct dngGrid_Position pos =
			dngGrid_positions[i];
		struct dngEntity * entity =
			dngGrid_getEntity(grid, pos);
		if (!entity)
			continue;
		combat->turns[combat->used++] = (struct Turn){
			.entity = entity,
			.initiative = dngIntBag_next(),
			.position = pos
		};
	}
	combat->round = 0;
	combat->turn = combat->used;
	qsort(combat->turns, combat->used, sizeof(struct Turn), cmpturns);
}

const struct dngCombat_Turn *
dngCombat_nextTurn(struct dngCombat * combat)
{
	assert(combat);
	return checkSides(combat)
		? nextTurn(combat)
		: NULL;
}
