#include "attr-primary.h"

#include "attr-primary-input.h"

#include <assert.h>

typedef struct dngAttrPrimary T;

T
dngAttrPrimary_fromInput(struct dngAttrPrimaryInput input)
{
	return (T){
		.agility = dngAttr_fromBase(input.agility),
		.intellect = dngAttr_fromBase(input.intellect),
		.strength = dngAttr_fromBase(input.strength)
	};
}

void
dngAttrPrimary_addInputToBase(T * self, struct dngAttrPrimaryInput input)
{
	assert(self);
	dngAttr_addBase(&self->agility, input.agility);
	dngAttr_addBase(&self->intellect, input.intellect);
	dngAttr_addBase(&self->strength, input.strength);
}
