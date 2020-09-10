#include "dice.h"

#include "int-bag.h"

const struct dngDice
dngDice_d4 = { .sides = 4 },
dngDice_d6 = { .sides = 6 },
dngDice_d8 = { .sides = 8 },
dngDice_d20 = { .sides = 20 },
dngDice_d100 = { .sides = 100 };

static int
rollDice(int sides)
{
	return dngIntBag_next() % sides + 1;
}

struct dngDice_Roll
dngDice_roll(struct dngDice dice)
{
	return (struct dngDice_Roll){
		.result = rollDice(dice.sides)
	};
}

struct dngDice_Chance
dngDice_rollChance(int percent)
{
	struct dngDice_Roll roll =
		dngDice_roll(dngDice_d100);

	return (struct dngDice_Chance){
		.percent = percent,
		.roll = roll,
		.success = roll.result <= percent
	};
}
