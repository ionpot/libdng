#include "race.h"

#include "attr-primary-input.h"

#include <assert.h>
#include <stdbool.h>

#define NO_BONUS dngAttrPrimaryInput_empty

struct dngAttrPrimaryInput
dngRace_getBonus(enum dngRace_Id id)
{
	switch (id) {
	case dngRace_HUMAN:
		return NO_BONUS;
	case dngRace_ORC:
		return (struct dngAttrPrimaryInput){
			.agility = 0,
			.intellect = -2,
			.strength = 2
		};
	}
	assert(false);
}
