#include "health.h"

#include "attr.h"
#include "int.h"

#include <assert.h>
#include <stdbool.h>

struct dngHealth
dngHealth_fromAttr(const struct dngAttr * attr)
{
	assert(attr);
	return dngHealth_fromBase(dngAttr_getTotal(attr));
}

struct dngHealth
dngHealth_fromBase(int amount)
{
	return (struct dngHealth){
		.total = dngAttr_fromBase(amount),
		.lost = 0
	};
}

void
dngHealth_gain(struct dngHealth * health, int amount)
{
	assert(health);
	dngInt_decr(&health->lost, amount);
}

int
dngHealth_getRemaining(const struct dngHealth * health)
{
	assert(health);
	return dngHealth_getTotal(health) - health->lost;
}

int
dngHealth_getTotal(const struct dngHealth * health)
{
	assert(health);
	return dngAttr_getTotal(&health->total);
}

bool
dngHealth_hasRemaining(const struct dngHealth * health)
{
	assert(health);
	return dngHealth_getRemaining(health) > 0;
}

void
dngHealth_lose(struct dngHealth * health, int amount)
{
	assert(health);
	health->lost += amount;
}

void
dngHealth_setBonus(struct dngHealth * health, int bonus)
{
	assert(health);
	dngAttr_setBonus(&health->total, bonus);
}
