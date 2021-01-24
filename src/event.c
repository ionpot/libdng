#include "event.h"

#include "ai.h"
#include "combat.h"
#include "combat-action.h"
#include "context.h"
#include "dice-pool.h"
#include "entity.h"
#include "entity-input.h"
#include "entities.h"
#include "event-list.h"
#include "grid.h"
#include "nodes.h"
#include "pool.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

static const union dngEvent_CombatAction_Info
no_combat_action_info;

static void
applyCombatAction(struct dngEvent_CombatAction event)
{
	struct dngEntity * target =
		dngCombatAction_getTarget(event.action);
	switch (event.action.id) {
	case dngCombatAction_DEFEND:
		return;
	case dngCombatAction_SPELL:
	case dngCombatAction_WEAPON:
		if (target)
			dngDamage_apply(event.info.attack.damage_total, target);
		return;
	}
	assert(false);
}

static union dngEvent_CombatAction_Info
getCombatActionInfo(
	struct dngCombatAction action,
	struct dngDicePool dice
) {
	switch (action.id) {
	case dngCombatAction_DEFEND:
		return no_combat_action_info;
	case dngCombatAction_SPELL:
		return (union dngEvent_CombatAction_Info){
			.attack = dngAttackEvent_ofSpell(action.params.spell, dice)
		};
	case dngCombatAction_WEAPON:
		return (union dngEvent_CombatAction_Info){
			.attack = dngAttackEvent_ofWeapon(action.params.weapon, dice)
		};
	}
	assert(false);
}

static bool
isPlayerTurn(struct dngContext * context)
{
	assert(context);
	return dngCombat_isTurnOfSide(context->combat, dngGrid_SIDE_A);
}

struct dngEvent_CombatAction
dngEvent_doCombatAction(struct dngContext * context)
{
	assert(context);
	dngDicePool_reset(context->dice);
	struct dngCombatAction action =
		isPlayerTurn(context)
			? context->input.action
			: dngAI_pickAction(context->combat);
	struct dngEvent_CombatAction event = {
		.action = action,
		.info = getCombatActionInfo(action, context->dice)
	};
	if (dngPool_noMem(context->dice.pool))
		dngContext_setNoMem(context);
	else
		applyCombatAction(event);
	return event;
}

void
dngEvent_doCombatBegin(struct dngContext * context)
{
	assert(context);

	dngDicePool_reset(context->dice);
	dngGrid_resetSide(&context->grid.side_b, context->entities);

	struct dngEntity * orc =
		dngEntities_next(context->entities);

	if (!orc)
		goto no_mem;

	struct dngEntityInput input =
		dngEntityInput_rollOrcFighter(context->dice, context->slots);

	if (dngPool_noMem(context->dice.pool))
		goto no_mem;
	if (dngNodes_noMem(context->slots.nodes))
		goto no_mem;

	*orc = dngEntity_fromInput(&input);

	struct dngGrid_Position position = {
		.line = dngGrid_LINE_FRONT,
		.side = dngGrid_SIDE_B,
		.slot = dngGrid_SLOT_2
	};
	dngGrid_putEntity(&context->grid, position, orc);
	dngCombat_init(context->combat, &context->grid);

	return;

no_mem:
	dngContext_setNoMem(context);
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
	case dngInput_COMBAT_ACTION:
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
