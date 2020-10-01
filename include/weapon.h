#ifndef LIBDNG_WEAPON_H
#define LIBDNG_WEAPON_H

enum dngWeapon_Id {
	dngWeapon_DAGGER,
	dngWeapon_LONG_AXE,
	dngWeapon_STAFF,
	dngWeapon_SWORD
};

int
dngWeapon_getInitiative(enum dngWeapon_Id);

#endif
