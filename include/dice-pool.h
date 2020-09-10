#ifndef LIBDNG_DICEPOOL_H
#define LIBDNG_DICEPOOL_H

#include "damage.h"
#include "dice.h"
#include "mempool.h"
#include "pool.h"

#include <stddef.h>

struct dngDicePool_Input {
	int count;
	struct dngDice dice;
};

struct dngDicePool_InputDamage {
	struct dngDicePool_Input roll;
	enum dngDamage_Type type;
};

struct dngDicePool_Roll {
	struct dngDicePool_Roll * next;
	int result;
};

struct dngDicePool_RollDamage {
	struct dngDicePool_InputDamage input;
	struct dngDicePool_RollDamage * next;
	struct dngDicePool_Roll * roll;
};

struct dngDicePool {
	struct dngPool * pool;
};

struct dngDicePool
dngDicePool_create(struct dngMemPool *);

int
dngDicePool_getTotal(const struct dngDicePool_Roll *);

int
dngDicePool_getTotalDamage(const struct dngDicePool_RollDamage *);

void
dngDicePool_reset(struct dngDicePool);

struct dngDicePool_Roll *
dngDicePool_roll(struct dngDicePool, struct dngDicePool_Input);

struct dngDicePool_RollDamage *
dngDicePool_rollDamage(struct dngDicePool, struct dngDicePool_InputDamage);

#endif
