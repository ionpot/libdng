#include "event.h"

#include <assert.h>
#include <stdbool.h>

typedef struct dngEvent T;

static const enum dngEvent_Id
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
	if (self->index < event_count)
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
dngEvent_create(void)
{
	return (T){
		.index = -1
	};
}

enum dngEvent_Id
dngEvent_jump(T * self, enum dngEvent_Id id)
{
	assert(self);
	self->index = seek(id);
	return current(self);
}

enum dngEvent_Id
dngEvent_next(T * self)
{
	assert(self);
	advance(self);
	return current(self);
}
