#include "event.h"

#include "context.h"
#include "dice-pool.h"
#include "entity.h"
#include "entities.h"
#include "grid.h"

#include <assert.h>

void
dngEvent_doCombatBegin(struct dngContext * context)
{
	assert(context);
	dngDicePool_reset(context->dices);
	dngGrid_resetSide(&context->grid.side_b, context->entities);
	struct dngEntity * orc =
		dngEntities_next(context->entities);
	struct dngEntity_Input input =
		dngDicePool_rollOrcFighter(context->dices, context->slots);
	struct dngGrid_Position position = {
		.line = dngGrid_LINE_FRONT,
		.side = dngGrid_SIDE_B,
		.slot = dngGrid_SLOT_2
	};
	*orc = dngEntity_fromInput(&input);
	dngGrid_putEntity(&context->grid, position, orc);
	dngCombat_init(context->combat, &context->grid);
}

int
dngEvent_doNextRound(struct dngContext * context)
{
	assert(context);
	dngCombat_nextRound(context->combat);
	return dngCombat_getRound(context->combat);
}
