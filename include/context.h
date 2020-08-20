#ifndef LIBDNG_CONTEXT_H
#define LIBDNG_CONTEXT_H

#include "event.h"

struct dngContext;

struct dngContext *
dngContext_create();

void
dngContext_destroy(struct dngContext *);

enum dngEvent_Id
dngContext_firstEvent(struct dngContext *);

enum dngEvent_Id
dngContext_nextEvent(struct dngContext *);

const struct dngGrid *
dngContext_getGrid(const struct dngContext *);

#endif
