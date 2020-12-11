#ifndef LIBDNG_DICEPOOL_H
#define LIBDNG_DICEPOOL_H

#include "dice.h"
#include "dice-rolls.h"
#include "int-bag.h"
#include "mempool.h"
#include "pool.h"

struct dngDicePool {
	struct dngIntBag * bag;
	struct dngPool * pool;
};

struct dngDicePool
dngDicePool_create(struct dngMemPool *, struct dngIntBag *);

void
dngDicePool_reset(struct dngDicePool);

struct dngDiceRolls *
dngDicePool_roll(struct dngDicePool, struct dngDice);

#endif
