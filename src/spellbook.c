#include "spellbook.h"

#include "spell-id.h"
#include "spell-pool.h"
#include "spell-slot.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct dngSpellbook T;

static void
addNewSlot(T * self, enum dngSpell_Id id, int limit)
{
	assert(self);
	struct dngSpellSlot * slot =
		dngSpellPool_nextSlot(self->pool);
	if (!slot) 
		return;
	*slot = dngSpellSlot_create(id, limit);
	slot->next = self->slots;
	self->slots = slot;
}

static struct dngSpellSlot *
seekSlot(const T * self, enum dngSpell_Id id)
{
	assert(self);
	struct dngSpellSlot * slot = self->slots;
	while (slot) {
		if (slot->id == id)
			break;
		slot = slot->next;
	}
	return slot;
}

T
dngSpellbook_create(struct dngSpellPool pool)
{
	return (T){
		.pool = pool,
		.slots = NULL
	};
}

void
dngSpellbook_add(T * self, enum dngSpell_Id id, int limit)
{
	assert(self);
	struct dngSpellSlot * slot =
		seekSlot(self, id);
	if (slot)
		dngSpellSlot_addLimit(slot, limit);
	else
		addNewSlot(self, id, limit);
}

bool
dngSpellbook_canCast(const T * self, enum dngSpell_Id id)
{
	assert(self);
	struct dngSpellSlot * slot =
		seekSlot(self, id);
	return slot
		? dngSpellSlot_canUse(slot)
		: false;
}
