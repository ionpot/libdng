#include "race.h"

#include "attr-primary.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

static const struct dngAttrPrimary_Input
orc_bonus = {
	.agility = 0,
	.intellect = -2,
	.strength = 2
};

const struct dngAttrPrimary_Input *
dngRace_getBonus(enum dngRace_Id id)
{
	switch (id) {
	case dngRace_HUMAN:
		return NULL;
	case dngRace_ORC:
		return &orc_bonus;
	default:
		assert(false);
	}
}
