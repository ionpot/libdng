#include "attr.h"

#include <assert.h>

typedef struct dngAttr T;

T
dngAttr_fromBase(int amount)
{
	return (T){
		.base = amount,
		.bonus = 0
	};
}

T
dngAttr_add(T a, T b)
{
	return (T){
		.base = a.base + b.base,
		.bonus = a.bonus + b.bonus
	};
}

void
dngAttr_addBase(T * self, int amount)
{
	assert(self);
	self->base += amount;
}

void
dngAttr_addBonus(T * self, int amount)
{
	assert(self);
	self->bonus += amount;
}

int
dngAttr_getTotal(T self)
{
	return self.base + self.bonus;
}

void
dngAttr_setBonus(T * self, int bonus)
{
	assert(self);
	self->bonus = bonus;
}
