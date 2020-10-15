#include "input.h"

#include "context.h"
#include "entity.h"
#include "entities.h"
#include "grid.h"
#include "input-def.h"

#include <assert.h>

void
dngInput_forAttack(struct dngContext * context, struct dngInput_Attack input)
{
	assert(context);
	context->input.attack = input;
}

void
dngInput_forEntity(struct dngContext * context, struct dngInput_NewEntity input)
{
	assert(context);
	struct dngEntity * entity = dngEntities_next(context->entities);
	if (!entity)
		return;
	struct dngEntity_Input entity_input = {
		.attr = input.attr,
		.klass = input.klass,
		.race = dngRace_HUMAN,
		.slots = context->slots,
		.weapon = input.weapon
	};
	*entity = dngEntity_fromInput(&entity_input);
	dngGrid_putEntity(&context->grid, input.position, entity);
}
