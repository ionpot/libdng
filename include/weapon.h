#ifndef LIBDNG_WEAPON_H
#define LIBDNG_WEAPON_H

#include "dice.h"

enum dngWeapon_Id {
	dngWeapon_DAGGER,
	dngWeapon_LONG_AXE,
	dngWeapon_SWORD
};

int
dngWeapon_getInitiative(enum dngWeapon_Id);

struct dngDice
dngWeapon_getDice(enum dngWeapon_Id);

#endif
