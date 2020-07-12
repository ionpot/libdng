#ifndef LIBDNG_ENTITY_H
#define LIBDNG_ENTITY_H

#include "attr.h"
#include "class.h"
#include "health.h"
#include "race.h"
#include "weapon.h"

#include <stdbool.h>

struct DNG_Entity {
	enum DNG_Race_Id race;
	enum DNG_Weapon_Id weapon;
	struct DNG_Attr_Primary attr_p;
	struct DNG_Attr_Secondary attr_s;
	struct DNG_Class klass;
	struct DNG_Health health;
};

struct DNG_Entity_Input {
	enum DNG_Class_Id klass;
	enum DNG_Race_Id race;
	enum DNG_Weapon_Id weapon;
	struct DNG_Attr_Input attr;
};

struct DNG_Entity_Pair {
	struct DNG_Entity * source;
	struct DNG_Entity * target;
};

struct DNG_Entity
DNG_Entity_fromInput(const struct DNG_Entity_Input *);

bool
DNG_Entity_isAlive(const struct DNG_Entity *);

#endif