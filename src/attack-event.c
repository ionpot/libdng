#include "attack-event.h"

#include "attack.h"
#include "damage.h"
#include "dice-pool.h"
#include "dice-rolls.h"
#include "spell-action.h"
#include "weapon-action.h"

#include <stddef.h>

typedef struct dngAttackEvent T;

T
dngAttackEvent_ofSpell(struct dngSpellAction spell, struct dngDicePool dice)
{
	struct dngAttack attack =
		dngAttack_fromSpell(spell);
	struct dngAttack_Roll attack_roll =
		dngAttack_roll(dice.bag);
	enum dngAttack_Result result =
		dngAttack_getResult(&attack, attack_roll);
	struct dngDamage damage =
		dngDamage_ofSpell(spell);
	struct dngDiceRolls * damage_roll =
		result == dngAttack_HIT
			? dngDamage_roll(&damage, dice)
			: NULL;
	int damage_total =
		dngDamage_getTotal(&damage, damage_roll);
	return (T){
		.attack = attack,
		.attack_roll = attack_roll,
		.damage = damage,
		.damage_roll = damage_roll,
		.damage_total = damage_total,
		.result = result
	};
}

T
dngAttackEvent_ofWeapon(struct dngWeaponAction weapon, struct dngDicePool dice)
{
	struct dngAttack attack =
		dngAttack_fromWeapon(weapon);
	struct dngAttack_Roll attack_roll =
		dngAttack_roll(dice.bag);
	enum dngAttack_Result result =
		dngAttack_getResult(&attack, attack_roll);
	struct dngDamage damage =
		dngDamage_ofWeapon(weapon);
	struct dngDiceRolls * damage_roll =
		result == dngAttack_HIT
			? dngDamage_roll(&damage, dice)
			: NULL;
	int damage_total =
		dngDamage_getTotal(&damage, damage_roll);
	return (T){
		.attack = attack,
		.attack_roll = attack_roll,
		.damage = damage,
		.damage_roll = damage_roll,
		.damage_total = damage_total,
		.result = result
	};
}
