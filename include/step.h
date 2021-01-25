#ifndef LIBDNG_STEP_H
#define LIBDNG_STEP_H

#include "attack-event.h"
#include "attr-primary-input.h"
#include "class.h"
#include "combat-action.h"
#include "context.h"
#include "entity.h"
#include "grid.h"
#include "weapon-id.h"

union dngStep_CombatAction_Info {
	struct dngAttackEvent attack;
};

struct dngStep_CombatAction {
	struct dngCombatAction action;
	union dngStep_CombatAction_Info info;
};

struct dngStep_PlayerEntity {
	struct dngAttrPrimaryInput attr;
	enum dngClass_Id klass;
	enum dngGrid_LineId line;
	enum dngGrid_SlotId slot;
	enum dngWeapon_Id weapon;
};

struct dngStep_CombatAction
dngStep_doCombatActionAI(struct dngContext *);

struct dngStep_CombatAction
dngStep_doCombatActionPlayer(struct dngContext *, struct dngCombatAction);

void
dngStep_doCombatBegin(struct dngContext *);

void
dngStep_doCombatNextRound(struct dngContext *);

void
dngStep_doCombatNextTurn(struct dngContext *);

struct dngEntity *
dngStep_doPlayerEntity(struct dngContext *, struct dngStep_PlayerEntity);

#endif
