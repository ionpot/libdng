#ifndef LIBDNG_WEAPON_ACTION_H
#define LIBDNG_WEAPON_ACTION_H

#include "entity.h"
#include "weapon-id.h"

struct dngWeaponAction {
	enum dngWeapon_Id id;
	struct dngEntity * target;
	struct dngEntity * user;
};

struct dngWeaponAction
dngWeaponAction_useEquipped(struct dngEntity_Pair);

#endif
