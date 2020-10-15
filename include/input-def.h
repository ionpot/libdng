#ifndef LIBDNG_INPUT_DEF_H
#define LIBDNG_INPUT_DEF_H

#include "attack.h"
#include "attr-primary.h"
#include "class.h"
#include "context.h"
#include "grid.h"
#include "spell-id.h"
#include "weapon.h"

enum dngInput_AttackType {
	dngInput_AttackType_SPELL,
	dngInput_AttackType_WEAPON
};

struct dngInput_Attack {
	enum dngSpell_Id spell;
	struct dngGrid_Position target;
	enum dngInput_AttackType type;
};

struct dngInput_NewEntity {
	struct dngAttrPrimary_Input attr;
	enum dngClass_Id klass;
	struct dngGrid_Position position;
	enum dngWeapon_Id weapon;
};

#endif
