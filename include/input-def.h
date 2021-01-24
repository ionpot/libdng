#ifndef LIBDNG_INPUT_DEF_H
#define LIBDNG_INPUT_DEF_H

#include "attr-primary-input.h"
#include "class.h"
#include "grid.h"
#include "weapon-id.h"

struct dngInput_NewEntity {
	struct dngAttrPrimaryInput attr;
	enum dngClass_Id klass;
	struct dngGrid_Position position;
	enum dngWeapon_Id weapon;
};

#endif
