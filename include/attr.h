#ifndef LIBDNG_ATTR_H
#define LIBDNG_ATTR_H

#include "dice.h"

struct DNG_Attr {
	int base;
	int bonus;
};

struct DNG_Attr_Input {
	int agility;
	int intellect;
	int strength;
};

struct DNG_Attr_Primary {
	struct DNG_Attr agility;
	struct DNG_Attr intellect;
	struct DNG_Attr strength;
};

struct DNG_Attr_Primary_Bonus {
	int agility;
	int intellect;
	int strength;
};

struct DNG_Attr_Roll {
	struct DNG_Dice_Roll roll_1;
	struct DNG_Dice_Roll roll_2;
	struct DNG_Dice_Roll roll_3;
};

struct DNG_Attr_Roll_Primary {
	struct DNG_Attr_Roll agility;
	struct DNG_Attr_Roll intellect;
	struct DNG_Attr_Roll strength;
};

struct DNG_Attr_Secondary {
	struct DNG_Attr armor;
	struct DNG_Attr dodge;
	struct DNG_Attr initiative;
	struct DNG_Attr will;
};

struct DNG_Attr
DNG_Attr_fromBase(int);

void
DNG_Attr_addBase(struct DNG_Attr *, int);

void
DNG_Attr_addBonus(struct DNG_Attr *, int);

void
DNG_Attr_addPrimaryBonusToBase(
	struct DNG_Attr_Primary *,
	const struct DNG_Attr_Primary_Bonus *
);

int
DNG_Attr_getRollTotal(const struct DNG_Attr_Roll *);

int
DNG_Attr_getTotal(const struct DNG_Attr *);

struct DNG_Attr_Roll_Primary
DNG_Attr_rollPrimary(void);

struct DNG_Attr_Primary
DNG_Attr_input2primary(const struct DNG_Attr_Input *);

struct DNG_Attr_Secondary
DNG_Attr_primary2secondary(const struct DNG_Attr_Primary *);

struct DNG_Attr_Input
DNG_Attr_primaryRoll2input(const struct DNG_Attr_Roll_Primary *);

void
DNG_Attr_setBonus(struct DNG_Attr *, int);

#endif
