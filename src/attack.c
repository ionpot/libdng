#include "attack.h"

#include "dice.h"
#include "entity.h"

#include <assert.h>

const int dngAttack_base_chance = 60;

static struct dngAttack_Defense
getDefense(const struct dngEntity * entity)
{
	assert(entity);
	return (struct dngAttack_Defense){
		.armor = entity->attr_s.armor,
		.dodge = entity->attr_s.dodge
	};
}

static int
getDefenseTotal(const struct dngAttack_Defense * defense)
{
	assert(defense);
	int total = 0;
	total += dngAttr_getTotal(&defense->armor);
	total += dngAttr_getTotal(&defense->dodge);
	return total;
}

static struct dngAttack_Offense
getOffense(const struct dngEntity * entity)
{
	assert(entity);
	return (struct dngAttack_Offense){
		.klass = entity->klass
	};
}

static int
getOffenseTotal(const struct dngAttack_Offense * offense)
{
	assert(offense);
	return dngClass_getAttackBonus(&offense->klass);
}

struct dngAttack
dngAttack_fromPair(struct dngEntity_Pair pair)
{
	assert(pair.source);
	assert(pair.target);
	return (struct dngAttack){
		.offense = getOffense(pair.source),
		.defense = getDefense(pair.target)
	};
}

struct dngAttack_Roll
dngAttack_roll(const struct dngAttack * attack)
{
	assert(attack);

	int hit_chance = dngAttack_base_chance;
	hit_chance += getOffenseTotal(&attack->offense);
	hit_chance -= getDefenseTotal(&attack->defense);

	struct dngDice_Chance chance =
		dngDice_rollChance(hit_chance);

	return (struct dngAttack_Roll){
		.result = chance.success
			? dngAttack_HIT
			: dngAttack_MISS,
		.hit_chance = hit_chance,
		.roll = chance.roll
	};
}
