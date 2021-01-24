#ifndef LIBDNG_HIT_CHANCE_H
#define LIBDNG_HIT_CHANCE_H

#include "chance.h"
#include "weapon-action.h"

#define dngHitChance_ZERO\
	(struct dngHitChance){\
		.armor = dngChance_ZERO,\
		.base = dngChance_ZERO,\
		.klass = dngChance_ZERO\
	}

struct dngHitChance {
	struct dngChance armor;
	struct dngChance base;
	struct dngChance klass;
};

struct dngHitChance
dngHitChance_withSpell(void);

struct dngHitChance
dngHitChance_withWeapon(struct dngWeaponAction);

struct dngChance
dngHitChance_getTotal(struct dngHitChance);

#endif
