#ifndef LIBDNG_ENTITY_H
#define LIBDNG_ENTITY_H

#include "attr-primary.h"
#include "class.h"
#include "health.h"
#include "race.h"
#include "weapon.h"

#include <stdbool.h>

struct dngEntity {
	struct dngAttrPrimary attr;
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

struct dngAttr
dngEntity_getArmor(const struct dngEntity *);

struct dngAttr
dngEntity_getDodge(const struct dngEntity *);

struct dngAttr
dngEntity_getInitiative(const struct dngEntity *);

struct dngAttr
dngEntity_getWill(const struct dngEntity *);

bool
dngEntity_isAlive(const struct dngEntity *);

#endif
