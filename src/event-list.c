#include "event-list.h"

#include "event-id.h"

#include <assert.h>
#include <stdbool.h>

typedef struct dngEventList T;

static const enum dngEvent_Id
event_order[] = {
	dngInput_ENTITY,
	dngEvent_COMBAT_BEGIN,
	dngEvent_NEXT_ROUND,
	dngInput_COMBAT_ACTION,
	dngEvent_COMBAT_ACTION,
	dngEvent_DAMAGE,
	dngEvent_COMBAT_END,
	dngEvent_END
};

static const int event_count =
	sizeof(event_order) / sizeof(*event_order);

static void
advance(T * self)
{
	assert(self);
	assert(event_count > 0);
	static const int max = event_count - 1;
	if (self->index < max)
		self->index++;
}

static enum dngEvent_Id
current(T * self)
{
	assert(self);
	assert(self->index >= 0);
	assert(self->index < event_count);
	return event_order[self->index];
}

static int
seek(enum dngEvent_Id id)
{
	for (int i = 0; i < event_count; i++) {
		if (event_order[i] == id)
			return i;
	}
	assert(false);
}

T
dngEventList_create(void)
{
	return (T){
		.index = -1
	};
}

void
dngEventList_jump(T * self, enum dngEvent_Id id)
{
	assert(self);
	self->index = seek(id);
}

enum dngEvent_Id
dngEventList_next(T * self)
{
	assert(self);
	advance(self);
	return current(self);
}
