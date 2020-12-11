#ifndef LIBDNG_ATTR_PRIMARY_H
#define LIBDNG_ATTR_PRIMARY_H

#include "attr.h"
#include "attr-primary-input.h"

struct dngAttrPrimary {
	struct dngAttr agility;
	struct dngAttr intellect;
	struct dngAttr strength;
};

struct dngAttrPrimary
dngAttrPrimary_fromInput(struct dngAttrPrimaryInput);

void
dngAttrPrimary_addInputToBase(
	struct dngAttrPrimary *,
	struct dngAttrPrimaryInput
);

#endif
