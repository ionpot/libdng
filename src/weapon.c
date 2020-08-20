#include "weapon.h"

#include "dice.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

static const struct dngWeapon_Bonus
dagger_bonus = { .initiative = 2 },
long_axe_bonus = { .initiative = -2 };

const struct dngWeapon_Bonus *
dngWeapon_getBonus(enum dngWeapon_Id id)
{
	switch (id) {
	case dngWeapon_DAGGER:
		return &dagger_bonus;
	case dngWeapon_LONG_AXE:
		return &long_axe_bonus;
	case dngWeapon_SWORD:
		return NULL;
	default:
		assert(false);
	}
}

struct dngDice
dngWeapon_getDice(enum dngWeapon_Id id)
{
	switch (id) {
	case dngWeapon_DAGGER:
		return dngDice_d4;
	case dngWeapon_LONG_AXE:
		return dngDice_d8;
	case dngWeapon_SWORD:
		return dngDice_d6;
	default:
		assert(false);
	}
}

struct dngWeapon_Bonus
dngWeapon_invertBonus(struct dngWeapon_Bonus bonus)
{
	return (struct dngWeapon_Bonus){
		.initiative = bonus.initiative * -1
	};
}
