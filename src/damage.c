#include "damage.h"

#include "attr.h"
#include "class.h"
#include "die.h"
#include "dice.h"
#include "dice-pool.h"
#include "dice-rolls.h"
#include "element.h"
#include "entity.h"
#include "source.h"
#include "weapon.h"
#include "weapon-id.h"

#include <assert.h>

typedef struct dngDamage T;

static const struct dngDamage_Bonus
no_bonus = {
	.intellect = 0,
	.strength = 0
};

int
getAttrBonus(struct dngAttr attr)
{
	return dngAttr_getTotal(&attr) / 2;
}

static struct dngDamage_Bonus
getIntellectBonus(const struct dngEntity * entity)
{
	assert(entity);
	struct dngDamage_Bonus bonus = no_bonus;
	bonus.intellect = getAttrBonus(entity->attr.intellect);
	return bonus;
}

static struct dngDamage_Bonus
getStrengthBonus(const struct dngEntity * entity)
{
	assert(entity);
	struct dngDamage_Bonus bonus = no_bonus;
	bonus.strength = getAttrBonus(entity->attr.strength);
	return bonus;
}

T
dngDamage_ofElectricBolt(const struct dngEntity * entity)
{
	assert(entity);
	struct dngDice base = dngDice_of(2, dngDie_d8);
	base.count += dngClass_getLevel(&entity->klass, dngClass_MAGE);
	return (T){
		.base = base,
		.bonus = no_bonus,
		.source = dngSource_AIR
	};
}

T
dngDamage_ofElementalBlast(
	enum dngElement element,
	const struct dngEntity * entity
) {
	assert(entity);
	return (T){
		.base = dngDice_of(1, dngDie_d4),
		.bonus = getIntellectBonus(entity),
		.source = dngSource_fromElement(element)
	};
}

T
dngDamage_ofEquipped(const struct dngEntity * entity)
{
	assert(entity);
	return dngDamage_ofWeapon(entity->weapon, entity);
}

T
dngDamage_ofWeapon(enum dngWeapon_Id id, const struct dngEntity * entity)
{
	assert(entity);
	return (T){
		.base = dngDice_of(1, dngWeapon_getDie(id)),
		.bonus = getStrengthBonus(entity),
		.source = dngSource_PHYSICAL
	};
}

int
dngDamage_getTotal(const T * self, const struct dngDiceRolls * rolls)
{
	assert(self);
	return dngDiceRolls_getTotal(rolls)
		+ self->bonus.intellect
		+ self->bonus.strength;
}

struct dngDiceRolls *
dngDamage_roll(const T * self, struct dngDicePool pool)
{
	assert(self);
	return dngDicePool_roll(pool, self->base);
}
