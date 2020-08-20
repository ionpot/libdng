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
	enum dngRace_Id race;
	enum dngWeapon_Id weapon;
	struct dngAttrPrimary attr_p;
	struct dngAttrSecondary attr_s;
	struct dngClass klass;
	struct dngHealth health;
};

struct dngEntity_Input {
	enum dngClass_Id klass;
	enum dngRace_Id race;
	enum dngWeapon_Id weapon;
	struct dngAttrPrimary_Input attr;
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
