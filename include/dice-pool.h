#ifndef LIBDNG_DICEPOOL_H
#define LIBDNG_DICEPOOL_H

#include "dice.h"
#include "mempool.h"

#include <stddef.h>

struct DNG_DicePool;

struct DNG_DicePool_Input {
	int count;
	struct DNG_Dice dice;
};

struct DNG_DicePool_Roll {
	int result;
	struct DNG_DicePool_Roll * next;
};

struct DNG_DicePool_Result {
	int total;
	struct DNG_DicePool_Input input;
	struct DNG_DicePool_Roll * roll;
};

struct DNG_DicePool
DNG_DicePool_create(struct DNG_MemPool *);

void
DNG_DicePool_reset(struct DNG_DicePool *);

struct DNG_DicePool_Result
DNG_DicePool_roll(struct DNG_DicePool *, struct DNG_DicePool_Input);

#endif
