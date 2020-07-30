#include "attr-primary.h"

#include "attr.h"

#include <assert.h>

struct DNG_AttrPrimary
DNG_AttrPrimary_fromInput(const struct DNG_AttrPrimary_Input * input)
{
	assert(input);
	return (struct DNG_AttrPrimary){
		.agility = DNG_Attr_fromBase(input->agility),
		.intellect = DNG_Attr_fromBase(input->intellect),
		.strength = DNG_Attr_fromBase(input->strength)
	};
}

void
DNG_AttrPrimary_addInputToBase(
	struct DNG_AttrPrimary * attr,
	const struct DNG_AttrPrimary_Input * input
) {
	assert(attr);
	assert(input);
	DNG_Attr_addBase(&attr->agility, input->agility);
	DNG_Attr_addBase(&attr->intellect, input->intellect);
	DNG_Attr_addBase(&attr->strength, input->strength);
}

struct DNG_AttrPrimary_Roll
DNG_AttrPrimary_roll(void)
{
	return (struct DNG_AttrPrimary_Roll){
		.agility = DNG_Attr_roll(),
		.intellect = DNG_Attr_roll(),
		.strength = DNG_Attr_roll()
	};
}

struct DNG_AttrPrimary_Input
DNG_AttrPrimary_roll2input(const struct DNG_AttrPrimary_Roll * roll)
{
	assert(roll);
	return (struct DNG_AttrPrimary_Input){
		.agility = DNG_Attr_getRollTotal(&roll->agility),
		.intellect = DNG_Attr_getRollTotal(&roll->intellect),
		.strength = DNG_Attr_getRollTotal(&roll->strength)
	};
}
