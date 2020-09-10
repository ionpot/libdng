#ifndef LIBDNG_ENTITY_H
#define LIBDNG_ENTITY_H

#include "attr-primary.h"
#include "attr-secondary.h"
#include "class.h"
#include "health.h"
#include "race.h"
#include "weapon.h"

#include <stdbool.h>

struct dngEntity {
	struct dngAttrPrimary attr_p;
	struct dngAttrSecondary attr_s;
	struct dngHealth health;
	struct dngClass klass;
	enum dngRace_Id race;
	enum dngWeapon_Id weapon;
};

struct dngEntity_Input {
	struct dngAttrPrimary_Input attr;
	enum dngClass_Id klass;
	enum dngRace_Id race;
	enum dngWeapon_Id weapon;
};

struct dngEntity_Pair {
	struct dngEntity * source;
	struct dngEntity * target;
};

struct dngEntity
dngEntity_fromInput(const struct dngEntity_Input *);

bool
dngEntity_isAlive(const struct dngEntity *);

#endif
