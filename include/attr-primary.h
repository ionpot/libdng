#ifndef LIBDNG_ATTR_PRIMARY_H
#define LIBDNG_ATTR_PRIMARY_H

#include "attr.h"

struct dngAttrPrimary {
	struct dngAttr agility;
	struct dngAttr intellect;
	struct dngAttr strength;
};

struct dngAttrPrimary_Input {
	int agility;
	int intellect;
	int strength;
};

struct dngAttrPrimary_Roll {
	struct dngAttr_Roll agility;
	struct dngAttr_Roll intellect;
	struct dngAttr_Roll strength;
};

struct dngAttrPrimary
dngAttrPrimary_fromInput(const struct dngAttrPrimary_Input *);

void
dngAttrPrimary_addInputToBase(
	struct dngAttrPrimary *,
	const struct dngAttrPrimary_Input *
);

struct dngAttrPrimary_Roll
dngAttrPrimary_roll(void);

struct dngAttrPrimary_Input
dngAttrPrimary_roll2input(const struct dngAttrPrimary_Roll *);

#endif
