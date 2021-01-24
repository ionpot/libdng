#include "spell-action.h"

#include "entity.h"
#include "spell-id.h"

#include <assert.h>
#include <stdbool.h>

typedef struct dngSpellAction T;

T
dngSpellAction_forElectricBolt(
	struct dngEntity * caster,
	struct dngSpellAction_ElectricBolt spell
) {
	return (T){
		.caster = caster,
		.id = dngSpell_ELECTRIC_BOLT,
		.params = { .electric_bolt = spell }
	};
}

T
dngSpellAction_forElementalBlast(
	struct dngEntity * caster,
	struct dngSpellAction_ElementalBlast spell
) {
	return (T){
		.caster = caster,
		.id = dngSpell_ELEMENTAL_BLAST,
		.params = { .elemental_blast = spell }
	};
}

struct dngEntity *
dngSpellAction_getTarget(T self)
{
	switch (self.id) {
	case dngSpell_ELECTRIC_BOLT:
		return self.params.electric_bolt.target;
	case dngSpell_ELEMENTAL_BLAST:
		return self.params.elemental_blast.target;
	}
	assert(false);
}
