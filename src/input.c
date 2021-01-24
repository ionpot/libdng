#include "input.h"

#include "combat-action.h"
#include "context.h"
#include "entity.h"
#include "entity-input.h"
#include "entities.h"
#include "grid.h"
#include "input-def.h"
#include "nodes.h"

#include <assert.h>

void
dngInput_forCombatAction(struct dngContext * context, struct dngCombatAction input)
{
	assert(context);
	context->input.action = input;
}

void
dngInput_forEntity(struct dngContext * context, struct dngInput_NewEntity input)
{
	assert(context);
	struct dngEntity * entity = dngEntities_next(context->entities);
	if (!entity)
		goto no_mem;
	struct dngEntityInput entity_input = {
		.attr = input.attr,
		.klass = input.klass,
		.race = dngRace_HUMAN,
		.slots = context->slots,
		.weapon = input.weapon
	};
	*entity = dngEntity_fromInput(&entity_input);
	if (dngNodes_noMem(context->slots.nodes))
		goto no_mem;
	dngGrid_putEntity(&context->grid, input.position, entity);
	return;
no_mem:
	dngContext_setNoMem(context);
}
