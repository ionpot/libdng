#include "attack.h"

#include "dice.h"
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
		.armor = dngAttr_getTotal(&armor),
		.dodge = dngAttr_getTotal(&dodge)
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

struct dngAttack_Roll
dngAttack_roll(const T * self)
{
	assert(self);

	int hit_chance = self->base;
	hit_chance += self->bonus.klass;
	hit_chance -= self->penalty.armor;
	hit_chance -= self->penalty.dodge;

	struct dngDice_Chance chance =
		dngDice_rollChance(hit_chance);

	return (struct dngAttack_Roll){
		.hit_chance = hit_chance,
		.result = chance.success
			? dngAttack_HIT
			: dngAttack_MISS,
		.roll = chance.roll
	};
}
