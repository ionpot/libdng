#include "ai.h"

#include "combat.h"
#include "combat-action.h"
#include "entity.h"
#include "grid-slot.h"
#include "weapon-action.h"

#include <assert.h>

struct dngCombatAction
dngAI_pickAction(const struct dngCombat * combat)
{
	assert(combat);
	struct dngGridSlot slot =
		dngCombat_getTurn(combat);
	struct dngEntity * target =
		dngCombat_findFirstReachable(combat, slot);
	if (!target) {
		return dngCombatAction_defend(slot.entity);
	}
	struct dngEntity_Pair pair = {
		.source = slot.entity,
		.target = target
	};
	return dngCombatAction_useWeapon(
		dngWeaponAction_useEquipped(pair)
	);
}
