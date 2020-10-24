#ifndef LIBDNG_EVENT_LIST_H
#define LIBDNG_EVENT_LIST_H

#include "event-id.h"

struct dngEventList {
	int index;
};

struct dngEventList
dngEventList_create(void);

void
dngEventList_jump(struct dngEventList *, enum dngEventId);

enum dngEventId
dngEventList_next(struct dngEventList *);

#endif
