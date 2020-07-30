#include "race.h"

#include "attr-primary.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

static const struct DNG_AttrPrimary_Input
orc_bonus = {
	.agility = 0,
	.intellect = -2,
	.strength = 2
};

const struct DNG_AttrPrimary_Input *
DNG_Race_getBonus(enum DNG_Race_Id id)
{
	switch (id) {
	case DNG_RACE_HUMAN:
		return NULL;
	case DNG_RACE_ORC:
		return &orc_bonus;
	default:
		assert(false);
	}
}
