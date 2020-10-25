#include "dice.h"

#include "int-bag.h"
#include "weapon.h"

#include <assert.h>

typedef struct dngDice T;

static const enum dngWeapon_Id
weapons[] = {
	dngWeapon_DAGGER,
	dngWeapon_LONG_AXE,
	dngWeapon_STAFF,
	dngWeapon_SWORD
};

static const int weapons_length =
	sizeof(weapons) / sizeof(*weapons);

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

enum dngWeapon_Id
dngDice_rollWeapon(struct dngIntBag * bag)
{
	assert(bag);
	assert(weapons_length > 0);
	assert(weapons_length <= dngIntBag_MAX_VALUE + 1);
	return weapons[dngIntBag_next(bag) % weapons_length];
}
