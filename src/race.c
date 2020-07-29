#include "race.h"

#include "attr.h"

#include <stddef.h>

static const struct DNG_Attr_Primary_Bonus
orc_bonus = {
	.agility = 0,
	.intellect = -2,
	.strength = 2
};

const struct DNG_Attr_Primary_Bonus *
DNG_Race_getBonus(enum DNG_Race_Id id)
{
	switch (id) {
	case DNG_RACE_ORC:
		return &orc_bonus;
	default:
		return NULL;
	}
}
