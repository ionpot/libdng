#include "spell-slot.h"

#include "spell-id.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct dngSpellSlot T;

T
dngSpellSlot_create(enum dngSpell_Id id, int limit)
{
	return (T){
		.id = id,
		.limit = limit,
		.next = NULL,
		.used = 0
	};
}

void
dngSpellSlot_addLimit(T * self, int limit)
{
	assert(self);
	assert(limit >= -1);
	if (self->limit == -1)
		return;
	if (limit == -1)
		self->limit = limit;
	else
		self->limit += limit;
}

bool
dngSpellSlot_canUse(const T * self)
{
	assert(self);
	if (self->limit == -1)
		return true;
	return self->used < self->limit;
}

void
dngSpellSlot_reset(T * self)
{
	assert(self);
	self->used = 0;
}

void
dngSpellSlot_use(T * self)
{
	assert(self);
	self->used++;
}
