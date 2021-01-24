#include "damage.h"

#include "attr.h"
#include "class.h"
#include "die.h"
#include "dice.h"
#include "dice-pool.h"
#include "dice-rolls.h"
#include "entity.h"
#include "health.h"
#include "source.h"
#include "spell-action.h"
#include "weapon.h"
#include "weapon-action.h"

#include <assert.h>
#include <stdbool.h>

typedef struct dngDamage T;

static const struct dngDamage_Bonus
no_bonus = {
	.intellect = 0,
	.strength = 0
};

int
getAttrBonus(struct dngAttr attr)
{
	return dngAttr_getTotal(attr) / 2;
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

void
dngDamage_apply(int total, struct dngEntity * target)
{
	assert(target);
	dngHealth_lose(&target->health, total);
}

T
dngDamage_ofElectricBolt(struct dngSpellAction spell)
{
	assert(spell.caster);
	struct dngDice base = dngDice_of(2, dngDie_d8);
	base.count += dngEntity_getClassLevel(spell.caster, dngClass_MAGE);
	return (T){
		.base = base,
		.bonus = no_bonus,
		.source = dngSource_AIR
	};
}

T
dngDamage_ofElementalBlast(struct dngSpellAction spell) {
	assert(spell.caster);
	struct dngSpellAction_ElementalBlast params =
		spell.params.elemental_blast;
	return (T){
		.base = dngDice_of(1, dngDie_d4),
		.bonus = getIntellectBonus(spell.caster),
		.source = dngSource_fromElement(params.element)
	};
}

T
dngDamage_ofSpell(struct dngSpellAction spell)
{
	switch (spell.id) {
	case dngSpell_ELECTRIC_BOLT:
		return dngDamage_ofElectricBolt(spell);
	case dngSpell_ELEMENTAL_BLAST:
		return dngDamage_ofElementalBlast(spell);
	}
	assert(false);
}

T
dngDamage_ofWeapon(struct dngWeaponAction weapon)
{
	assert(weapon.user);
	return (T){
		.base = dngDice_of(1, dngWeapon_getDie(weapon.id)),
		.bonus = getStrengthBonus(weapon.user),
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
