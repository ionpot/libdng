#include "spell-slot.h"

#include "spell-id.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

struct dngSpellSlot
dngSpellSlot_create(enum dngSpell_Id id, int limit)
{
	return (struct dngSpellSlot){
		.id = id,
		.limit = limit,
		.next = NULL,
		.used = 0
	};
}

void
dngSpellSlot_addLimit(struct dngSpellSlot * slot, int limit)
{
	assert(slot);
	assert(limit >= -1);
	if (slot->limit == -1)
		return;
	if (limit == -1)
		slot->limit = limit;
	else
		slot->limit += limit;
}

bool
dngSpellSlot_canUse(const struct dngSpellSlot * slot)
{
	assert(slot);
	if (slot->limit == -1)
		return true;
	return slot->used < slot->limit;
}

void
dngSpellSlot_reset(struct dngSpellSlot * slot)
{
	assert(slot);
	slot->used = 0;
}

void
dngSpellSlot_use(struct dngSpellSlot * slot)
{
	assert(slot);
	slot->used++;
}
