#ifndef LIBDNG_RACE_H
#define LIBDNG_RACE_H

#include "attr-primary.h"

enum dngRace_Id {
	dngRace_HUMAN,
	dngRace_ORC
};

const struct dngAttrPrimary_Input *
dngRace_getBonus(enum dngRace_Id);

#endif
