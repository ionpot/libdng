#ifndef LIBDNG_EVENT_H
#define LIBDNG_EVENT_H

#include "attack-event.h"
#include "combat-action.h"
#include "context.h"
#include "event-id.h"

union dngEvent_CombatAction_Info {
	struct dngAttackEvent attack;
};

struct dngEvent_CombatAction {
	struct dngCombatAction action;
	union dngEvent_CombatAction_Info info;
};

struct dngEvent_CombatAction
dngEvent_doCombatAction(struct dngContext *);

void
dngEvent_doCombatBegin(struct dngContext *);

int
dngEvent_doNextRound(struct dngContext *);

enum dngEvent_Id
dngEvent_next(struct dngContext *);

#endif
