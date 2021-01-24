#include "attack.h"

#include "chance.h"
#include "evasion.h"
#include "hit-chance.h"
#include "int-bag.h"
#include "spell-action.h"
#include "weapon-action.h"

#include <assert.h>
#include <stdbool.h>

typedef struct dngAttack T;

T
dngAttack_fromSpell(struct dngSpellAction spell)
{
	return (T){
		.evasion = dngEvasion_fromSpell(spell),
		.hit_chance = dngHitChance_withSpell()
	};
}

T
dngAttack_fromWeapon(struct dngWeaponAction weapon)
{
	return (T){
		.evasion = dngEvasion_fromWeapon(weapon),
		.hit_chance = dngHitChance_withWeapon(weapon)
	};
}

enum dngAttack_Result
dngAttack_getResult(const T * self, struct dngAttack_Roll roll)
{
	assert(self);
	struct dngChance hit_chance =
		dngHitChance_getTotal(self->hit_chance);
	struct dngChance evasion =
		dngEvasion_getTotal(self->evasion);
	if (dngChance_isSuccess(hit_chance, roll.attack))
		if (!dngChance_isSuccess(evasion, roll.evasion))
			return dngAttack_HIT;
	return dngAttack_MISS;
}

struct dngAttack_Roll
dngAttack_roll(struct dngIntBag * bag)
{
	assert(bag);
	return (struct dngAttack_Roll){
		.attack = dngChance_roll(bag),
		.evasion = dngChance_roll(bag)
	};
}
