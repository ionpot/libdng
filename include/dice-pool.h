#ifndef LIBDNG_DICEPOOL_H
#define LIBDNG_DICEPOOL_H

#include "dice.h"
#include "mempool.h"

#include <stddef.h>

struct dngDicePool_Input {
	int count;
	struct dngDice dice;
};

struct dngDicePool_Roll {
	int result;
	struct dngDicePool_Roll * next;
};

struct dngDicePool {
	struct dngPool * pool;
};

struct dngDicePool
dngDicePool_create(struct dngMemPool *);

int
dngDicePool_getTotal(const struct dngDicePool_Roll *);

void
dngDicePool_reset(struct dngDicePool);

struct dngDicePool_Roll *
dngDicePool_roll(struct dngDicePool, struct dngDicePool_Input);

#endif
