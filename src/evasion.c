#include "evasion.h"

#include "attr.h"
#include "chance.h"
#include "entity.h"
#include "spell-action.h"
#include "weapon-action.h"

typedef struct dngEvasion T;

T
dngEvasion_fromSpell(struct dngSpellAction spell)
{
	const struct dngEntity * target =
		dngSpellAction_getTarget(spell);
	if (!target) {
		return dngEvasion_ZERO;
	}
	int will = dngAttr_getTotal(
		dngEntity_getWill(target)
	);
	return (T){
		.dodge = dngChance_ZERO,
		.willpower = dngChance_percent(will)
	};
}

T
dngEvasion_fromWeapon(struct dngWeaponAction weapon)
{
	if (!weapon.target) {
		return dngEvasion_ZERO;
	}
	struct dngAttr dodge =
		dngEntity_getDodge(weapon.target);
	int total = dngAttr_getTotal(dodge);
	return (T){
		.dodge = dngChance_percent(total),
		.willpower = dngChance_ZERO
	};
}

struct dngChance
dngEvasion_getTotal(T self)
{
	struct dngChance total = self.dodge;
	dngChance_add(&total, self.willpower);
	return total;
}
