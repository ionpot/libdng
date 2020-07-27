#include "health.h"

#include "attr.h"
#include "int.h"

#include <assert.h>
#include <stdbool.h>

struct DNG_Health
DNG_Health_fromAttr(const struct DNG_Attr * attr)
{
	assert(attr);
	return DNG_Health_fromBase(DNG_Attr_getTotal(attr));
}

struct DNG_Health
DNG_Health_fromBase(int amount)
{
	return (struct DNG_Health){
		.total = DNG_Attr_fromBase(amount),
		.lost = 0
	};
}

void
DNG_Health_gain(struct DNG_Health * health, int amount)
{
	assert(health);
	DNG_Int_decr(&health->lost, amount);
}

int
DNG_Health_getRemaining(const struct DNG_Health * health)
{
	assert(health);
	return DNG_Health_getTotal(health) - health->lost;
}

int
DNG_Health_getTotal(const struct DNG_Health * health)
{
	assert(health);
	return DNG_Attr_getTotal(&health->total);
}

bool
DNG_Health_hasRemaining(const struct DNG_Health * health)
{
	assert(health);
	return DNG_Health_getRemaining(health) > 0;
}

void
DNG_Health_lose(struct DNG_Health * health, int amount)
{
	assert(health);
	health->lost += amount;
}

void
DNG_Health_setBonus(struct DNG_Health * health, int bonus)
{
	assert(health);
	DNG_Attr_setBonus(&health->total, bonus);
}
