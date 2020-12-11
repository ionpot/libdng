#ifndef LIBDNG_ENTITY_INPUT_H
#define LIBDNG_ENTITY_INPUT_H

#include "attr-primary-input.h"
#include "class.h"
#include "dice-pool.h"
#include "race.h"
#include "spell-slots.h"
#include "weapon-id.h"

struct dngEntityInput {
	struct dngAttrPrimaryInput attr;
	enum dngClass_Id klass;
	enum dngRace_Id race;
	struct dngSpellSlots slots;
	enum dngWeapon_Id weapon;
};

struct dngEntityInput
dngEntityInput_rollOrcFighter(struct dngDicePool, struct dngSpellSlots);

#endif
