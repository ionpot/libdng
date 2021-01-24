#ifndef LIBDNG_COMBAT_ACTION_H
#define LIBDNG_COMBAT_ACTION_H

#include "entity.h"
#include "spell-action.h"
#include "weapon-action.h"

enum dngCombatAction_Id {
	dngCombatAction_DEFEND,
	dngCombatAction_SPELL,
	dngCombatAction_WEAPON
};

union dngCombatAction_Params {
	struct dngEntity * defending;
	struct dngSpellAction spell;
	struct dngWeaponAction weapon;
};

struct dngCombatAction {
	enum dngCombatAction_Id id;
	union dngCombatAction_Params params;
};

struct dngCombatAction
dngCombatAction_castSpell(struct dngSpellAction);

struct dngCombatAction
dngCombatAction_defend(struct dngEntity *);

struct dngCombatAction
dngCombatAction_useWeapon(struct dngWeaponAction);

struct dngEntity *
dngCombatAction_getTarget(struct dngCombatAction);

#endif
