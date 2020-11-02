#ifndef LIBDNG_EVENT_H
#define LIBDNG_EVENT_H

#include "context.h"
#include "event-id.h"

void
dngEvent_doCombatBegin(struct dngContext *);

int
dngEvent_doNextRound(struct dngContext *);

enum dngEvent_Id
dngEvent_next(struct dngContext *);

#endif
