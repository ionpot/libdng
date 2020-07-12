#include "attr.h"

#include "dice.h"

#include <assert.h>

static struct DNG_Attr
fromBase(int amount)
{
	return (struct DNG_Attr){
		.base = amount,
		.bonus = 0
	};
}

static struct DNG_Attr_Roll
rollAttr(void)
{
	return (struct DNG_Attr_Roll){
		.roll_1 = DNG_Dice_roll(DNG_Dice_d6),
		.roll_2 = DNG_Dice_roll(DNG_Dice_d6),
		.roll_3 = DNG_Dice_roll(DNG_Dice_d6)
	};
}

static struct DNG_Attr
sumAttr(struct DNG_Attr a, struct DNG_Attr b)
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
DNG_Attr_getTotal(struct DNG_Attr attr)
{
	return attr.base + attr.bonus;
}

struct DNG_Attr_Roll_Primary
DNG_Attr_rollPrimary(void)
{
	return (struct DNG_Attr_Roll_Primary){
		.agility = rollAttr(),
		.intellect = rollAttr(),
		.strength = rollAttr()
	};
}

struct DNG_Attr_Primary
DNG_Attr_input2primary(const struct DNG_Attr_Input * input)
{
	assert(input);
	return (struct DNG_Attr_Primary){
		.agility = fromBase(input->agility),
		.intellect = fromBase(input->intellect),
		.strength = fromBase(input->strength)
	};
}

struct DNG_Attr_Secondary
DNG_Attr_primary2secondary(const struct DNG_Attr_Primary * primary)
{
	assert(primary);
	return (struct DNG_Attr_Secondary){
		.armor = fromBase(0),
		.dodge = primary->agility,
		.initiative = sumAttr(primary->agility, primary->intellect),
		.will = primary->intellect
	};
}

struct DNG_Attr_Input
DNG_Attr_primaryRoll2input(const struct DNG_Attr_Roll_Primary * primary)
{
	assert(primary);
	return (struct DNG_Attr_Input){
		.agility = DNG_Attr_getRollTotal(&primary->agility),
		.intellect = DNG_Attr_getRollTotal(&primary->intellect),
		.strength = DNG_Attr_getRollTotal(&primary->strength)
	};
}
