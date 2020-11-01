#ifndef LIBDNG_EVENT_H
#define LIBDNG_EVENT_H

#include "context.h"

void
dngEvent_doCombatBegin(struct dngContext *);

int
dngEvent_doNextRound(struct dngContext *);

#endif
