#include "attr-secondary.h"

#include "attr.h"
#include "attr-primary.h"

#include <assert.h>

struct DNG_AttrSecondary
DNG_AttrSecondary_fromPrimary(const struct DNG_AttrPrimary * primary)
{
	assert(primary);
	return (struct DNG_AttrSecondary){
		.armor = DNG_Attr_fromBase(0),
		.dodge = primary->agility,
		.initiative = DNG_Attr_add(primary->agility, primary->intellect),
		.will = primary->intellect
	};
}
