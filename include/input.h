#ifndef LIBDNG_INPUT_H
#define LIBDNG_INPUT_H

#include "attack.h"
#include "attr.h"
#include "class.h"
#include "context.h"
#include "grid.h"
#include "weapon.h"

/*
 * the entity who has the current turn will attack the target position
 */
struct dngInput_Attack {
	struct dngGrid_Position target;
	enum dngAttack_Type type;
};

void
dngInput_doAttack(struct dngContext *, struct dngInput_Attack);

/*
 * create the entity using choices from player
 */
struct dngInput_Entity {
	struct dngAttr_Roll_Primary attr;
	enum dngClass_Id klass;
	enum dngWeapon_Id weapon;
};

void
dngInput_doEntity(struct dngContext *, struct dngInput_Entity);

#endif
