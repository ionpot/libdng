#include "event-list.h"

#include "event-id.h"

#include <assert.h>
#include <stdbool.h>

typedef struct dngEventList T;

static const enum dngEventId
event_order[] = {
	dngInput_ENTITY,
	dngOutput_COMBAT_BEGIN,
	dngOutput_NEXT_ROUND,
	dngInput_ATTACK,
	dngOutput_ATTACK,
	dngOutput_DAMAGE,
	dngOutput_COMBAT_END,
	dngOutput_END
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

static enum dngEventId
current(T * self)
{
	assert(self);
	assert(self->index >= 0);
	assert(self->index < event_count);
	return event_order[self->index];
}

static int
seek(enum dngEventId id)
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
dngEventList_jump(T * self, enum dngEventId id)
{
	assert(self);
	self->index = seek(id);
}

enum dngEventId
dngEventList_next(T * self)
{
	assert(self);
	advance(self);
	return current(self);
}
