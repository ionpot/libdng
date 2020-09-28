#include "spellbook.h"

#include "spell-id.h"
#include "spell-slot.h"
#include "spell-slots.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct dngSpellbook T;

static void
addNewSlot(T * self, enum dngSpell_Id id, int limit)
{
	assert(self);
	struct dngSpellSlot * slot =
		dngSpellSlots_next(self->slots);
	if (!slot) 
		return;
	*slot = dngSpellSlot_create(id, limit);
	slot->next = self->slot;
	self->slot = slot;
}

static struct dngSpellSlot *
seekSlot(const T * self, enum dngSpell_Id id)
{
	assert(self);
	struct dngSpellSlot * slot = self->slot;
	while (slot) {
		if (slot->id == id)
			break;
		slot = slot->next;
	}
	return slot;
}

T
dngSpellbook_create(struct dngSpellSlots slots)
{
	return (T){
		.slots = slots,
		.slot = NULL
	};
}

T
dngSpellbook_forWizard(struct dngSpellSlots slots)
{
	T book = dngSpellbook_create(slots);
	addNewSlot(&book, dngSpell_ELECTRIC_BOLT, 1);
	addNewSlot(&book, dngSpell_ELEMENTAL_BLAST, -1);
	return book;
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

void
dngSpellbook_clear(T * self)
{
	assert(self);
	struct dngSpellSlot * slot = self->slot;
	struct dngSpellSlot * tmp;
	while (slot) {
		tmp = slot->next;
		dngSpellSlots_return(self->slots, slot);
		slot = tmp;
	}
	self->slot = NULL;
}
