#include "health.h"

#include "attr.h"
#include "int.h"

#include <assert.h>
#include <stdbool.h>

typedef struct dngHealth T;

T
dngHealth_fromAttr(struct dngAttr attr)
{
	return dngHealth_fromBase(dngAttr_getTotal(attr));
}

T
dngHealth_fromBase(int amount)
{
	return (T){
		.lost = 0,
		.total = dngAttr_fromBase(amount)
	};
}

void
dngHealth_gain(T * self, int amount)
{
	assert(self);
	dngInt_decr(&self->lost, amount);
}

int
dngHealth_getRemaining(T self)
{
	return dngHealth_getTotal(self) - self.lost;
}

int
dngHealth_getTotal(T self)
{
	return dngAttr_getTotal(self.total);
}

bool
dngHealth_hasRemaining(T self)
{
	return dngHealth_getRemaining(self) > 0;
}

void
dngHealth_lose(T * self, int amount)
{
	assert(self);
	self->lost += amount;
}

void
dngHealth_setBonus(T * self, int bonus)
{
	assert(self);
	dngAttr_setBonus(&self->total, bonus);
}
