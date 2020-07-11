#ifndef LIBDNG_DICE_H
#define LIBDNG_DICE_H

#include <stdbool.h>

struct DNG_Dice {
	int sides;
};

struct DNG_Dice_Roll {
	int result;
	int sides;
};

struct DNG_Dice_Chance {
	bool success;
	int percent;
	struct DNG_Dice_Roll roll;
};

const struct DNG_Dice
DNG_Dice_d4,
DNG_Dice_d6,
DNG_Dice_d8,
DNG_Dice_d20,
DNG_Dice_d100;

void
DNG_Dice_init(void);

struct DNG_Dice_Roll
DNG_Dice_roll(struct DNG_Dice);

struct DNG_Dice_Chance
DNG_Dice_rollChance(int percent);

#endif
