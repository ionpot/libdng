#ifndef LIBDNG_ATTR_H
#define LIBDNG_ATTR_H

#include "dice.h"

struct DNG_Attr {
	int base;
	int bonus;
};

struct DNG_Attr_Roll {
	struct DNG_Dice_Roll roll_1;
	struct DNG_Dice_Roll roll_2;
	struct DNG_Dice_Roll roll_3;
};

struct DNG_Attr
DNG_Attr_fromBase(int);

struct DNG_Attr
DNG_Attr_add(struct DNG_Attr, struct DNG_Attr);

void
DNG_Attr_addBase(struct DNG_Attr *, int);

void
DNG_Attr_addBonus(struct DNG_Attr *, int);

int
DNG_Attr_getRollTotal(const struct DNG_Attr_Roll *);

int
DNG_Attr_getTotal(const struct DNG_Attr *);

struct DNG_Attr_Roll
DNG_Attr_roll(void);

void
DNG_Attr_setBonus(struct DNG_Attr *, int);

#endif
