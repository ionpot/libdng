#ifndef LIBDNG_ATTR_SECONDARY_H
#define LIBDNG_ATTR_SECONDARY_H

#include "attr.h"
#include "attr-primary.h"

struct DNG_AttrSecondary {
	struct DNG_Attr armor;
	struct DNG_Attr dodge;
	struct DNG_Attr initiative;
	struct DNG_Attr will;
};

struct DNG_AttrSecondary
DNG_AttrSecondary_fromPrimary(const struct DNG_AttrPrimary *);

#endif
