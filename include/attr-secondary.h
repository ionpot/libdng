#ifndef LIBDNG_ATTR_SECONDARY_H
#define LIBDNG_ATTR_SECONDARY_H

#include "attr.h"
#include "attr-primary.h"

struct dngAttrSecondary {
	struct dngAttr armor;
	struct dngAttr dodge;
	struct dngAttr initiative;
	struct dngAttr will;
};

struct dngAttrSecondary
dngAttrSecondary_fromPrimary(const struct dngAttrPrimary *);

#endif
