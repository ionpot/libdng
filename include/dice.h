#ifndef LIBDNG_DICE_H
#define LIBDNG_DICE_H

#include "int-bag.h"

#include <stdbool.h>

struct dngDice {
	int sides;
};

struct dngDice_Roll {
	int result;
};

struct dngDice_Chance {
	int percent;
	struct dngDice_Roll roll;
	bool success;
};

const struct dngDice
dngDice_d4,
dngDice_d6,
dngDice_d8,
dngDice_d20,
dngDice_d100;

struct dngDice_Roll
dngDice_roll(struct dngDice, struct dngIntBag *);

struct dngDice_Chance
dngDice_rollChance(int percent, struct dngIntBag *);

#endif
