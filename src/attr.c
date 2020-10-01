#include "attr.h"

#include <assert.h>

struct dngAttr
dngAttr_fromBase(int amount)
{
	return (struct dngAttr){
		.base = amount,
		.bonus = 0
	};
}

struct dngAttr
dngAttr_add(struct dngAttr a, struct dngAttr b)
{
	return (struct dngAttr){
		.base = a.base + b.base,
		.bonus = a.bonus + b.bonus
	};
}

void
dngAttr_addBase(struct dngAttr * attr, int amount)
{
	assert(attr);
	attr->base += amount;
}

void
dngAttr_addBonus(struct dngAttr * attr, int amount)
{
	assert(attr);
	attr->bonus += amount;
}

int
dngAttr_getTotal(const struct dngAttr * attr)
{
	assert(attr);
	return attr->base + attr->bonus;
}

void
dngAttr_setBonus(struct dngAttr * attr, int bonus)
{
	assert(attr);
	attr->bonus = bonus;
}
