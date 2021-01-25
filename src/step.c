#include "step.h"

#include "ai.h"
#include "attack-event.h"
#include "combat.h"
#include "combat-action.h"
#include "context.h"
#include "dice-pool.h"
#include "entity.h"
#include "entity-input.h"
#include "entities.h"
#include "grid.h"
#include "nodes.h"
#include "pool.h"
#include "step-id.h"
#include "steps.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

static const union dngStep_CombatAction_Info
no_combat_action_info;

static enum dngStep_Id
checkStep(struct dngContext * context, enum dngStep_Id id)
{
	assert(context);
	switch (id) {
	case dngStep_COMBAT_ACTION_AI:
		if (dngCombat_isTurnOfSide(context->combat, dngGrid_SIDE_B))
			return id;
		goto next;
	case dngStep_COMBAT_ACTION_PLAYER:
		if (dngCombat_isTurnOfSide(context->combat, dngGrid_SIDE_A))
			return id;
		goto next;
	case dngStep_COMBAT_BEGIN:
		return id;
	case dngStep_COMBAT_END:
		if (dngCombat_hasEnded(context->combat))
			return id;
		return checkStep(context, dngStep_COMBAT_NEXT_ROUND);
	case dngStep_COMBAT_NEXT_ROUND:
		if (dngCombat_isEndOfRound(context->combat))
			return id;
		goto next;
	case dngStep_COMBAT_NEXT_TURN:
	case dngStep_END:
	case dngStep_PLAYER_ENTITY:
		return id;
	}
	assert(false);
next:
	return checkStep(context, dngSteps_next(id));
}

static void
nextStep(struct dngContext * context)
{
	assert(context);
	enum dngStep_Id id =
		dngSteps_next(dngSteps_get(context->steps));
	dngSteps_goto(&context->steps, checkStep(context, id));
}

static void
applyCombatAction(struct dngStep_CombatAction event)
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

static union dngStep_CombatAction_Info
getCombatActionInfo(
	struct dngCombatAction action,
	struct dngDicePool dice
) {
	switch (action.id) {
	case dngCombatAction_DEFEND:
		return no_combat_action_info;
	case dngCombatAction_SPELL:
		return (union dngStep_CombatAction_Info){
			.attack = dngAttackEvent_ofSpell(action.params.spell, dice)
		};
	case dngCombatAction_WEAPON:
		return (union dngStep_CombatAction_Info){
			.attack = dngAttackEvent_ofWeapon(action.params.weapon, dice)
		};
	}
	assert(false);
}

struct dngStep_CombatAction
dngStep_doCombatActionAI(struct dngContext * context)
{
	assert(context);
	dngDicePool_reset(context->dice);
	struct dngCombatAction action =
		dngAI_pickAction(context->combat);
	struct dngStep_CombatAction output = {
		.action = action,
		.info = getCombatActionInfo(action, context->dice)
	};
	if (dngPool_noMem(context->dice.pool)) {
		dngContext_setNoMem(context);
	} else {
		applyCombatAction(output);
		nextStep(context);
	}
	return output;
}

struct dngStep_CombatAction
dngStep_doCombatActionPlayer(
	struct dngContext * context,
	struct dngCombatAction input
) {
	assert(context);
	dngDicePool_reset(context->dice);
	struct dngStep_CombatAction output = {
		.action = input,
		.info = getCombatActionInfo(input, context->dice)
	};
	if (dngPool_noMem(context->dice.pool)) {
		dngContext_setNoMem(context);
	} else {
		applyCombatAction(output);
		nextStep(context);
	}
	return output;
}

void
dngStep_doCombatBegin(struct dngContext * context)
{
	assert(context);

	dngDicePool_reset(context->dice);
	dngGrid_resetSide(&context->grid.side_b, context->entities);

	struct dngEntity * orc =
		dngEntities_next(context->entities);

	if (!orc)
		goto no_mem;

	struct dngEntityInput entity_input =
		dngEntityInput_rollOrcFighter(context->dice, context->slots);

	if (dngPool_noMem(context->dice.pool))
		goto no_mem;
	if (dngNodes_noMem(context->slots.nodes))
		goto no_mem;

	*orc = dngEntity_fromInput(entity_input);

	struct dngGrid_Position position = {
		.line = dngGrid_LINE_FRONT,
		.side = dngGrid_SIDE_B,
		.slot = dngGrid_SLOT_2
	};
	dngGrid_putEntity(&context->grid, position, orc);
	dngCombat_init(context->combat, &context->grid);

	nextStep(context);

	return;

no_mem:
	dngContext_setNoMem(context);
}

void
dngStep_doCombatNextRound(struct dngContext * context)
{
	assert(context);
	dngCombat_nextRound(context->combat);
	nextStep(context);
}

struct dngEntity *
dngStep_doPlayerEntity(
	struct dngContext * context,
	struct dngStep_PlayerEntity input
) {
	assert(context);

	struct dngEntity * entity =
		dngEntities_next(context->entities);

	if (!entity)
		goto no_mem;

	*entity = dngEntity_fromInput(
		(struct dngEntityInput){
			.attr = input.attr,
			.klass = input.klass,
			.race = dngRace_HUMAN,
			.slots = context->slots,
			.weapon = input.weapon
		}
	);

	if (dngNodes_noMem(context->slots.nodes))
		goto no_mem;

	struct dngGrid_Position position = {
		.line = input.line,
		.side = dngGrid_SIDE_A,
		.slot = input.slot
	};
	dngGrid_putEntity(&context->grid, position, entity);

	nextStep(context);

	return entity;

no_mem:
	dngContext_setNoMem(context);
	return NULL;
}
