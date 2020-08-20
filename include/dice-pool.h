#ifndef LIBDNG_DICEPOOL_H
#define LIBDNG_DICEPOOL_H

#include "dice.h"
#include "mempool.h"

#include <stddef.h>

struct dngDicePool;

struct dngDicePool_Input {
	int count;
	struct dngDice dice;
};

struct dngDicePool_Roll {
	int result;
	struct dngDicePool_Roll * next;
};

struct dngDicePool_Result {
	int total;
	struct dngDicePool_Input input;
	struct dngDicePool_Roll * roll;
};

struct dngDicePool
dngDicePool_create(struct dngMemPool *);

void
dngDicePool_reset(struct dngDicePool *);

struct dngDicePool_Result
dngDicePool_roll(struct dngDicePool *, struct dngDicePool_Input);

#endif
