#include "weapon.h"

#include "dice.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

static const struct DNG_Weapon_Bonus
dagger_bonus = { .initiative = 2 },
long_axe_bonus = { .initiative = -2 };

const struct DNG_Weapon_Bonus *
DNG_Weapon_getBonus(enum DNG_Weapon_Id id)
{
	switch (id) {
	case DNG_WEAPON_DAGGER:
		return &dagger_bonus;
	case DNG_WEAPON_LONG_AXE:
		return &long_axe_bonus;
	case DNG_WEAPON_SWORD:
		return NULL;
	default:
		assert(false);
	}
}

struct DNG_Dice
DNG_Weapon_getDice(enum DNG_Weapon_Id id)
{
	switch (id) {
	case DNG_WEAPON_DAGGER:
		return DNG_Dice_d4;
	case DNG_WEAPON_LONG_AXE:
		return DNG_Dice_d8;
	case DNG_WEAPON_SWORD:
		return DNG_Dice_d6;
	default:
		assert(false);
	}
}

struct DNG_Weapon_Bonus
DNG_Weapon_invertBonus(struct DNG_Weapon_Bonus bonus)
{
	return (struct DNG_Weapon_Bonus){
		.initiative = bonus.initiative * -1
	};
}
