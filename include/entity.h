#ifndef LIBDNG_ENTITY_H
#define LIBDNG_ENTITY_H

#include "attr-primary.h"
#include "class.h"
#include "entity-input.h"
#include "health.h"
#include "race.h"
#include "spellbook.h"
#include "weapon-id.h"

#include <stdbool.h>

struct dngEntity {
	struct dngAttrPrimary attr;
	struct dngHealth health;
	struct dngClass klass;
	enum dngRace_Id race;
	struct dngSpellbook spellbook;
	enum dngWeapon_Id weapon;
};

struct dngEntity_Pair {
	struct dngEntity * source;
	struct dngEntity * target;
};

struct dngEntity
dngEntity_fromInput(const struct dngEntityInput *);

void
dngEntity_clear(struct dngEntity *);

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
