#include "attr.h"

#include "dice.h"

#include <assert.h>

struct dngAttr
dngAttr_fromBase(int amount)
{
	return (struct dngAttr){
		.base = amount,
		.bonus = 0
	};
}

struct dngAttr
dngAttr_add(struct dngAttr a, struct dngAttr b)
{
	return (struct dngAttr){
		.base = a.base + b.base,
		.bonus = a.bonus + b.bonus
	};
}

void
dngAttr_addBase(struct dngAttr * attr, int amount)
{
	assert(attr);
	attr->base += amount;
}

void
dngAttr_addBonus(struct dngAttr * attr, int amount)
{
	assert(attr);
	attr->bonus += amount;
}

int
dngAttr_getRollTotal(const struct dngAttr_Roll * roll)
{
	assert(roll);
	return roll->roll_1.result
		+ roll->roll_2.result
		+ roll->roll_3.result;
}

int
dngAttr_getTotal(const struct dngAttr * attr)
{
	assert(attr);
	return attr->base + attr->bonus;
}

struct dngAttr_Roll
dngAttr_roll(void)
{
	return (struct dngAttr_Roll){
		.roll_1 = dngDice_roll(dngDice_d6),
		.roll_2 = dngDice_roll(dngDice_d6),
		.roll_3 = dngDice_roll(dngDice_d6)
	};
}

void
dngAttr_setBonus(struct dngAttr * attr, int bonus)
{
	assert(attr);
	attr->bonus = bonus;
}
