#ifndef LIBDNG_ATTR_PRIMARY_H
#define LIBDNG_ATTR_PRIMARY_H

#include "attr.h"

struct DNG_AttrPrimary {
	struct DNG_Attr agility;
	struct DNG_Attr intellect;
	struct DNG_Attr strength;
};

struct DNG_AttrPrimary_Input {
	int agility;
	int intellect;
	int strength;
};

struct DNG_AttrPrimary_Roll {
	struct DNG_Attr_Roll agility;
	struct DNG_Attr_Roll intellect;
	struct DNG_Attr_Roll strength;
};

struct DNG_AttrPrimary
DNG_AttrPrimary_fromInput(const struct DNG_AttrPrimary_Input *);

void
DNG_AttrPrimary_addInputToBase(
	struct DNG_AttrPrimary *,
	const struct DNG_AttrPrimary_Input *
);

struct DNG_AttrPrimary_Roll
DNG_AttrPrimary_roll(void);

struct DNG_AttrPrimary_Input
DNG_AttrPrimary_roll2input(const struct DNG_AttrPrimary_Roll *);

#endif
