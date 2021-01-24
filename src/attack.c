#include "attack.h"

#include "entity.h"

#include <assert.h>

#define BASE_CHANCE 60

typedef struct dngAttack T;

static struct dngAttack_Bonus
getBonus(const struct dngEntity * entity)
{
	assert(entity);
	return (struct dngAttack_Bonus){
		.klass = dngClass_getAttackBonus(&entity->klass)
	};
}

static struct dngAttack_Penalty
getPenalty(const struct dngEntity * entity)
{
	assert(entity);
	struct dngAttr armor = dngEntity_getArmor(entity);
	struct dngAttr dodge = dngEntity_getDodge(entity);
	return (struct dngAttack_Penalty){
		.armor = dngAttr_getTotal(armor),
		.dodge = dngAttr_getTotal(dodge)
	};
}

T
dngAttack_fromPair(struct dngEntity_Pair pair)
{
	assert(pair.source);
	assert(pair.target);
	return (T){
		.base = BASE_CHANCE,
		.bonus = getBonus(pair.source),
		.penalty = getPenalty(pair.target)
	};
}

int
dngAttack_getPercent(const T * self)
{
	assert(self);
	int percent = self->base;
	percent += self->bonus.klass;
	percent -= self->penalty.armor;
	percent -= self->penalty.dodge;
	return percent;
}
