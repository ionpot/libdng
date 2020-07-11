#ifndef LIBDNG_WEAPON_H
#define LIBDNG_WEAPON_H

#include "dice.h"

enum DNG_Weapon_Id {
	DNG_WEAPON_DAGGER,
	DNG_WEAPON_LONG_AXE,
	DNG_WEAPON_SWORD,
	DNG_WEAPON_UNARMED
};

struct DNG_Weapon_Bonus {
	int initiative;
};

struct DNG_Weapon {
	struct DNG_Dice dice;
	struct DNG_Weapon_Bonus bonus;
};

const struct DNG_Weapon *
DNG_Weapon_get(enum DNG_Weapon_Id);

struct DNG_Weapon_Bonus
DNG_Weapon_invertBonus(struct DNG_Weapon_Bonus);

#endif
