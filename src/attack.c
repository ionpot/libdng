#include "attack.h"

#include "dice.h"
#include "entity.h"

#include <assert.h>

const int base_chance = 60;

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
	return (struct dngAttack_Penalty){
		.armor = dngAttr_getTotal(&entity->attr_s.armor),
		.dodge = dngAttr_getTotal(&entity->attr_s.dodge)
	};
}

struct dngAttack
dngAttack_fromPair(struct dngEntity_Pair pair)
{
	assert(pair.source);
	assert(pair.target);
	return (struct dngAttack){
		.base = base_chance,
		.bonus = getBonus(pair.source),
		.penalty = getPenalty(pair.target)
	};
}

struct dngAttack_Roll
dngAttack_roll(const struct dngAttack * attack)
{
	assert(attack);

	int hit_chance = attack->base;
	hit_chance += attack->bonus.klass;
	hit_chance -= attack->penalty.armor;
	hit_chance -= attack->penalty.dodge;

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
