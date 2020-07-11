#ifndef LIBDNG_CONTEXT_H
#define LIBDNG_CONTEXT_H

#include "event.h"

struct DNG_Context;

struct DNG_Context *
DNG_Context_create();

void
DNG_Context_destroy(struct DNG_Context *);

enum DNG_Event_Id
DNG_Context_firstEvent(struct DNG_Context *);

enum DNG_Event_Id
DNG_Context_nextEvent(struct DNG_Context *);

const struct DNG_Grid *
DNG_Context_getGrid(const struct DNG_Context *);

#endif
