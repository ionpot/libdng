#ifndef LIBDNG_WEAPON_H
#define LIBDNG_WEAPON_H

#include "dice.h"

enum DNG_Weapon_Id {
	DNG_WEAPON_DAGGER,
	DNG_WEAPON_LONG_AXE,
	DNG_WEAPON_SWORD
};

struct DNG_Weapon_Bonus {
	int initiative;
};

const struct DNG_Weapon_Bonus *
DNG_Weapon_getBonus(enum DNG_Weapon_Id);

struct DNG_Dice
DNG_Weapon_getDice(enum DNG_Weapon_Id);

struct DNG_Weapon_Bonus
DNG_Weapon_invertBonus(struct DNG_Weapon_Bonus);

#endif
