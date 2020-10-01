#include "dice.h"

#include "int-bag.h"

#include <assert.h>

typedef struct dngDice T;

const T
dngDice_d4 = { .sides = 4 },
dngDice_d6 = { .sides = 6 },
dngDice_d8 = { .sides = 8 },
dngDice_d20 = { .sides = 20 },
dngDice_d100 = { .sides = 100 };

struct dngDice_Roll
dngDice_roll(T self, struct dngIntBag * bag)
{
	assert(bag);
	return (struct dngDice_Roll){
		.result = dngIntBag_next(bag) % self.sides + 1
	};
}

struct dngDice_Chance
dngDice_rollChance(int percent, struct dngIntBag * bag)
{
	assert(bag);

	struct dngDice_Roll roll =
		dngDice_roll(dngDice_d100, bag);

	return (struct dngDice_Chance){
		.percent = percent,
		.roll = roll,
		.success = roll.result <= percent
	};
}
