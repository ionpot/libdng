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
struct DNG_Input_Attack {
	enum DNG_Attack_Type type;
	struct DNG_Grid_Position target;
};

void
DNG_Input_doAttack(struct DNG_Context *, struct DNG_Input_Attack);

/*
 * create the entity using choices from player
 */
struct DNG_Input_Entity {
	enum DNG_Class_Id klass;
	enum DNG_Weapon_Id weapon;
	struct DNG_Attr_Roll_Primary attr;
};

void
DNG_Input_doEntity(struct DNG_Context *, struct DNG_Input_Entity);

#endif
