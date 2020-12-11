#include "attr-primary-input.h"

#include "die.h"
#include "dice-pool.h"
#include "dice-rolls.h"

typedef struct dngAttrPrimaryInput T;

T
dngAttrPrimaryInput_fromRolls(struct dngAttrPrimaryInput_Rolls rolls)
{
	return (T){
		.agility = dngDiceRolls_getTotal(rolls.agility),
		.intellect = dngDiceRolls_getTotal(rolls.intellect),
		.strength = dngDiceRolls_getTotal(rolls.strength)
	};
}

struct dngDice
dngAttrPrimaryInput_getDice(void)
{
	return (struct dngDice){
		.count = 3,
		.die = dngDie_d6
	};
}

T
dngAttrPrimaryInput_random(struct dngDicePool pool)
{
	return dngAttrPrimaryInput_fromRolls(
		dngAttrPrimaryInput_roll(pool)
	);
}

struct dngAttrPrimaryInput_Rolls
dngAttrPrimaryInput_roll(struct dngDicePool pool)
{
	struct dngDice dice = dngAttrPrimaryInput_getDice();
	return (struct dngAttrPrimaryInput_Rolls){
		.agility = dngDicePool_roll(pool, dice),
		.intellect = dngDicePool_roll(pool, dice),
		.strength = dngDicePool_roll(pool, dice)
	};
}
