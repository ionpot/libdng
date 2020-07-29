#ifndef LIBDNG_RACE_H
#define LIBDNG_RACE_H

#include "attr.h"

enum DNG_Race_Id {
	DNG_RACE_HUMAN,
	DNG_RACE_ORC
};

const struct DNG_Attr_Primary_Bonus *
DNG_Race_getBonus(enum DNG_Race_Id);

#endif
