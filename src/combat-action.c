#include "combat-action.h"

#include "entity.h"
#include "spell-action.h"
#include "weapon-action.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct dngCombatAction T;

T
dngCombatAction_castSpell(struct dngSpellAction spell)
{
	return (T){
		.id = dngCombatAction_SPELL,
		.params = { .spell = spell }
	};
}

T
dngCombatAction_useWeapon(struct dngWeaponAction weapon)
{
	return (T){
		.id = dngCombatAction_WEAPON,
		.params = { .weapon = weapon }
	};
}

struct dngEntity *
dngCombatAction_getTarget(T self)
{
	switch (self.id) {
	case dngCombatAction_DEFEND:
		return NULL;
	case dngCombatAction_SPELL:
		return dngSpellAction_getTarget(self.params.spell);
	case dngCombatAction_WEAPON:
		return self.params.weapon.target;
	}
	assert(false);
}
