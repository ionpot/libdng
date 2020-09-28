#include "weapon.h"

#include "dice.h"

#include <assert.h>
#include <stdbool.h>

int
dngWeapon_getInitiative(enum dngWeapon_Id id)
{
	switch (id) {
	case dngWeapon_DAGGER:
		return 2;
	case dngWeapon_LONG_AXE:
		return -2;
	case dngWeapon_STAFF:
	case dngWeapon_SWORD:
		return 0;
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
	case dngWeapon_STAFF:
	case dngWeapon_SWORD:
		return dngDice_d6;
	default:
		assert(false);
	}
}
