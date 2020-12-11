#ifndef LIBDNG_DICE_H
#define LIBDNG_DICE_H

#include "die.h"

struct dngDice {
	int count;
	struct dngDie die;
};

struct dngDice
dngDice_of(int count, struct dngDie);

#endif
