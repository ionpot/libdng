#include "event.h"

#include "combat.h"
#include "context.h"
#include "dice-pool.h"
#include "entity.h"
#include "entities.h"
#include "event-list.h"
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

enum dngEvent_Id
dngEvent_next(struct dngContext * context)
{
	assert(context);
	enum dngEvent_Id id =
		dngEventList_next(&context->events);
	switch (id) {
	case dngInput_ATTACK:
		if (dngCombat_isTurnOfSide(context->combat, dngGrid_SIDE_A))
			return id;
		break;
	case dngEvent_COMBAT_END:
		if (dngCombat_hasEnded(context->combat))
			return id;
		dngEventList_jump(&context->events, dngEvent_COMBAT_BEGIN);
		break;
	case dngEvent_NEXT_ROUND:
		if (dngCombat_isEndOfRound(context->combat))
			return id;
		break;
	default:
		return id;
	}
	return dngEvent_next(context);
}
