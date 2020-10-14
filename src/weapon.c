#include "weapon.h"

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
	}
	assert(false);
}
