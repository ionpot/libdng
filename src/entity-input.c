#include "entity-input.h"

#include "attr-primary-input.h"
#include "class.h"
#include "dice-pool.h"
#include "race.h"
#include "spell-slots.h"
#include "weapon.h"

typedef struct dngEntityInput T;

T
dngEntityInput_rollOrcFighter(
	struct dngDicePool pool,
	struct dngSpellSlots slots
) {
	return (T){
		.attr = dngAttrPrimaryInput_random(pool),
		.klass = dngClass_FIGHTER,
		.race = dngRace_ORC,
		.slots = slots,
		.weapon = dngWeapon_random(pool.bag)
	};
}
