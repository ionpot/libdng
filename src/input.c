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
	struct dngEntity * entity = dngEntities_next(&context->entities);
	if (!entity)
		return;
	*entity = dngEntity_fromInput((struct dngEntity_Input){
		.attr = input.attr,
		.klass = input.klass,
		.race = dngRace_HUMAN,
		.slots = context->slots,
		.weapon = input.weapon
	});
	dngGrid_putEntity(&context->grid, input.position, entity);
}
