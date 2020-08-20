#ifndef LIBDNG_ATTR_H
#define LIBDNG_ATTR_H

#include "dice.h"

struct dngAttr {
	int base;
	int bonus;
};

struct dngAttr_Roll {
	struct dngDice_Roll roll_1;
	struct dngDice_Roll roll_2;
	struct dngDice_Roll roll_3;
};

struct dngAttr
dngAttr_fromBase(int);

struct dngAttr
dngAttr_add(struct dngAttr, struct dngAttr);

void
dngAttr_addBase(struct dngAttr *, int);

void
dngAttr_addBonus(struct dngAttr *, int);

int
dngAttr_getRollTotal(const struct dngAttr_Roll *);

int
dngAttr_getTotal(const struct dngAttr *);

struct dngAttr_Roll
dngAttr_roll(void);

void
dngAttr_setBonus(struct dngAttr *, int);

#endif
