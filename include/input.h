#ifndef LIBDNG_INPUT_H
#define LIBDNG_INPUT_H

#include "combat-action.h"
#include "context.h"
#include "input-def.h"

void
dngInput_forCombatAction(struct dngContext *, struct dngCombatAction);

void
dngInput_forEntity(struct dngContext *, struct dngInput_NewEntity);

#endif
