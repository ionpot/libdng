#ifndef LIBDNG_RACE_H
#define LIBDNG_RACE_H

#include "attr-primary-input.h"

enum dngRace_Id {
	dngRace_HUMAN,
	dngRace_ORC
};

struct dngAttrPrimaryInput
dngRace_getBonus(enum dngRace_Id);

#endif
