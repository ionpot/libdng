#ifndef LIBDNG_EVASION_H
#define LIBDNG_EVASION_H

#include "chance.h"
#include "spell-action.h"
#include "weapon-action.h"

#define dngEvasion_ZERO\
	(struct dngEvasion){\
		.dodge = dngChance_ZERO,\
		.willpower = dngChance_ZERO\
	}

struct dngEvasion {
	struct dngChance dodge;
	struct dngChance willpower;
};

struct dngEvasion
dngEvasion_fromSpell(struct dngSpellAction);

struct dngEvasion
dngEvasion_fromWeapon(struct dngWeaponAction);

struct dngChance
dngEvasion_getTotal(struct dngEvasion);

#endif
