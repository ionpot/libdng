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
	enum dngAttack_Type type;
	struct dngGrid_Position target;
};

void
dngInput_doAttack(struct dngContext *, struct dngInput_Attack);

/*
 * create the entity using choices from player
 */
struct dngInput_Entity {
	enum dngClass_Id klass;
	enum dngWeapon_Id weapon;
	struct dngAttr_Roll_Primary attr;
};

void
dngInput_doEntity(struct dngContext *, struct dngInput_Entity);

#endif
