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

struct dngAttrPrimary_Roll
dngAttrPrimary_roll(void)
{
	return (struct dngAttrPrimary_Roll){
		.agility = dngAttr_roll(),
		.intellect = dngAttr_roll(),
		.strength = dngAttr_roll()
	};
}

struct dngAttrPrimary_Input
dngAttrPrimary_roll2input(const struct dngAttrPrimary_Roll * roll)
{
	assert(roll);
	return (struct dngAttrPrimary_Input){
		.agility = dngAttr_getRollTotal(&roll->agility),
		.intellect = dngAttr_getRollTotal(&roll->intellect),
		.strength = dngAttr_getRollTotal(&roll->strength)
	};
}
