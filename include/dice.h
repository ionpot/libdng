#ifndef LIBDNG_DICE_H
#define LIBDNG_DICE_H

#include <stdbool.h>

struct dngDice {
	int sides;
};

struct dngDice_Roll {
	int result;
	int sides;
};

struct dngDice_Chance {
	bool success;
	int percent;
	struct dngDice_Roll roll;
};

const struct dngDice
dngDice_d4,
dngDice_d6,
dngDice_d8,
dngDice_d20,
dngDice_d100;

void
dngDice_init(void);

struct dngDice_Roll
dngDice_roll(struct dngDice);

struct dngDice_Chance
dngDice_rollChance(int percent);

#endif
