#include "steps.h"

#include "int.h"
#include "step-id.h"

#include <assert.h>
#include <stdbool.h>

typedef struct dngSteps T;

static const enum dngStep_Id
step_order[] = {
	dngStep_PLAYER_ENTITY,
	dngStep_COMBAT_BEGIN,
	dngStep_COMBAT_NEXT_ROUND,
	dngStep_COMBAT_NEXT_TURN,
	dngStep_COMBAT_ACTION_AI,
	dngStep_COMBAT_ACTION_PLAYER,
	dngStep_COMBAT_END,
	dngStep_END
};

static const int step_count =
	sizeof(step_order) / sizeof(*step_order);

static int
seek(enum dngStep_Id id)
{
	for (int i = 0; i < step_count; i++) {
		if (step_order[i] == id)
			return i;
	}
	assert(false);
}

T
dngSteps_create(void)
{
	return (T){.index = 0};
}

enum dngStep_Id
dngSteps_get(T self)
{
	assert(self.index >= 0);
	assert(self.index < step_count);
	return step_order[self.index];
}

void
dngSteps_goto(T * self, enum dngStep_Id id)
{
	assert(self);
	self->index = seek(id);
}

enum dngStep_Id
dngSteps_next(enum dngStep_Id step)
{
	static const int max = step_count - 1;
	int i = seek(step) + 1;
	return step_order[dngInt_min(i, max)];
}
