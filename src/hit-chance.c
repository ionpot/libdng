#include "hit-chance.h"

#include "attr.h"
#include "chance.h"
#include "class.h"
#include "entity.h"
#include "weapon-action.h"

#include <assert.h>

#define BASE_CHANCE_SPELL 100
#define BASE_CHANCE_WEAPON 60

typedef struct dngHitChance T;

T
dngHitChance_withSpell(void)
{
	T self = dngHitChance_ZERO;
	self.base = dngChance_percent(BASE_CHANCE_SPELL);
	return self;
}

T
dngHitChance_withWeapon(struct dngWeaponAction weapon)
{
	assert(weapon.user);
	assert(weapon.target);
	int armor = dngAttr_getTotal(
		dngEntity_getArmor(weapon.target)
	);
	int klass = dngClass_getAttackBonus(&weapon.user->klass);
	return (T){
		.armor = dngChance_percent(armor),
		.base = dngChance_percent(BASE_CHANCE_WEAPON),
		.klass = dngChance_percent(klass)
	};
}

struct dngChance
dngHitChance_getTotal(T self)
{
	struct dngChance total = self.base;
	dngChance_add(&total, self.klass);
	dngChance_sub(&total, self.armor);
	return total;
}
