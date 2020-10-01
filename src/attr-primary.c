#include "attr-primary.h"

#include "attr.h"

#include <assert.h>

struct dngAttrPrimary
dngAttrPrimary_fromInput(const struct dngAttrPrimary_Input * input)
{
	assert(input);
	return (struct dngAttrPrimary){
		.agility = dngAttr_fromBase(input->agility),
		.intellect = dngAttr_fromBase(input->intellect),
		.strength = dngAttr_fromBase(input->strength)
	};
}

void
dngAttrPrimary_addInputToBase(
	struct dngAttrPrimary * attr,
	const struct dngAttrPrimary_Input * input
) {
	assert(attr);
	assert(input);
	dngAttr_addBase(&attr->agility, input->agility);
	dngAttr_addBase(&attr->intellect, input->intellect);
	dngAttr_addBase(&attr->strength, input->strength);
}
