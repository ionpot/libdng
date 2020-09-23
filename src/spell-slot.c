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
