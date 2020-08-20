#ifndef LIBDNG_WEAPON_H
#define LIBDNG_WEAPON_H

#include "dice.h"

enum dngWeapon_Id {
	dngWeapon_DAGGER,
	dngWeapon_LONG_AXE,
	dngWeapon_SWORD
};

struct dngWeapon_Bonus {
	int initiative;
};

const struct dngWeapon_Bonus *
dngWeapon_getBonus(enum dngWeapon_Id);

struct dngDice
dngWeapon_getDice(enum dngWeapon_Id);

struct dngWeapon_Bonus
dngWeapon_invertBonus(struct dngWeapon_Bonus);

#endif
