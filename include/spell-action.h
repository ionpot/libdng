#ifndef LIBDNG_SPELL_ACTION_H
#define LIBDNG_SPELL_ACTION_H

#include "element.h"
#include "entity.h"
#include "spell-id.h"

struct dngSpellAction_ElectricBolt {
	struct dngEntity * target;
};

struct dngSpellAction_ElementalBlast {
	enum dngElement element;
	struct dngEntity * target;
};

union dngSpellAction_Union {
	struct dngSpellAction_ElectricBolt electric_bolt;
	struct dngSpellAction_ElementalBlast elemental_blast;
};

struct dngSpellAction {
	struct dngEntity * caster;
	enum dngSpell_Id id;
	union dngSpellAction_Union params;
};

struct dngSpellAction
dngSpellAction_forElectricBolt(
	struct dngEntity * caster,
	struct dngSpellAction_ElectricBolt
);

struct dngSpellAction
dngSpellAction_forElementalBlast(
	struct dngEntity * caster,
	struct dngSpellAction_ElementalBlast
);

struct dngEntity *
dngSpellAction_getTarget(struct dngSpellAction);

#endif
