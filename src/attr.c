#include "attr.h"

#include "dice.h"

#include <assert.h>

struct DNG_Attr
DNG_Attr_fromBase(int amount)
{
	return (struct DNG_Attr){
		.base = amount,
		.bonus = 0
	};
}

struct DNG_Attr
DNG_Attr_add(struct DNG_Attr a, struct DNG_Attr b)
{
	return (struct DNG_Attr){
		.base = a.base + b.base,
		.bonus = a.bonus + b.bonus
	};
}

void
DNG_Attr_addBase(struct DNG_Attr * attr, int amount)
{
	assert(attr);
	attr->base += amount;
}

void
DNG_Attr_addBonus(struct DNG_Attr * attr, int amount)
{
	assert(attr);
	attr->bonus += amount;
}

int
DNG_Attr_getRollTotal(const struct DNG_Attr_Roll * roll)
{
	assert(roll);
	return roll->roll_1.result
		+ roll->roll_2.result
		+ roll->roll_3.result;
}

int
DNG_Attr_getTotal(const struct DNG_Attr * attr)
{
	assert(attr);
	return attr->base + attr->bonus;
}

struct DNG_Attr_Roll
DNG_Attr_roll(void)
{
	return (struct DNG_Attr_Roll){
		.roll_1 = DNG_Dice_roll(DNG_Dice_d6),
		.roll_2 = DNG_Dice_roll(DNG_Dice_d6),
		.roll_3 = DNG_Dice_roll(DNG_Dice_d6)
	};
}

void
DNG_Attr_setBonus(struct DNG_Attr * attr, int bonus)
{
	assert(attr);
	attr->bonus = bonus;
}
