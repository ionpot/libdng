#ifndef LIBDNG_ATTR_PRIMARY_INPUT_H
#define LIBDNG_ATTR_PRIMARY_INPUT_H

#include "dice.h"
#include "dice-pool.h"
#include "dice-rolls.h"

struct dngAttrPrimaryInput_Rolls {
	struct dngDiceRolls * agility;
	struct dngDiceRolls * intellect;
	struct dngDiceRolls * strength;
};

struct dngAttrPrimaryInput {
	int agility;
	int intellect;
	int strength;
};

const struct dngAttrPrimaryInput
dngAttrPrimaryInput_empty = {
	.agility = 0,
	.intellect = 0,
	.strength = 0
};

struct dngAttrPrimaryInput
dngAttrPrimaryInput_fromRolls(struct dngAttrPrimaryInput_Rolls);

struct dngDice
dngAttrPrimaryInput_getDice(void);

struct dngAttrPrimaryInput
dngAttrPrimaryInput_random(struct dngDicePool);

struct dngAttrPrimaryInput_Rolls
dngAttrPrimaryInput_roll(struct dngDicePool);

#endif
