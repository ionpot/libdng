#ifndef LIBDNG_ATTACK_EVENT_H
#define LIBDNG_ATTACK_EVENT_H

#include "attack.h"
#include "damage.h"
#include "dice-pool.h"
#include "dice-rolls.h"
#include "spell-action.h"
#include "weapon-action.h"

struct dngAttackEvent {
	struct dngAttack attack;
	struct dngAttack_Roll attack_roll;
	struct dngDamage damage;
	struct dngDiceRolls * damage_roll;
	int damage_total;
	enum dngAttack_Result result;
};

struct dngAttackEvent
dngAttackEvent_ofSpell(struct dngSpellAction, struct dngDicePool);

struct dngAttackEvent
dngAttackEvent_ofWeapon(struct dngWeaponAction, struct dngDicePool);

#endif
