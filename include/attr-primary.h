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

struct dngAttrPrimary
dngAttrPrimary_fromInput(const struct dngAttrPrimary_Input *);

void
dngAttrPrimary_addInputToBase(
	struct dngAttrPrimary *,
	const struct dngAttrPrimary_Input *
);

#endif
