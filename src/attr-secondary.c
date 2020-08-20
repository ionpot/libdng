#include "attr-secondary.h"

#include "attr.h"
#include "attr-primary.h"

#include <assert.h>

struct dngAttrSecondary
dngAttrSecondary_fromPrimary(const struct dngAttrPrimary * primary)
{
	assert(primary);
	return (struct dngAttrSecondary){
		.armor = dngAttr_fromBase(0),
		.dodge = primary->agility,
		.initiative = dngAttr_add(primary->agility, primary->intellect),
		.will = primary->intellect
	};
}
