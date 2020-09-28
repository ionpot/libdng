#ifndef LIBDNG_SPELLBOOK_H
#define LIBDNG_SPELLBOOK_H

#include "spell-id.h"
#include "spell-slot.h"
#include "spell-slots.h"

#include <stdbool.h>

struct dngSpellbook {
	struct dngSpellSlots slots;
	struct dngSpellSlot * slot;
};

struct dngSpellbook
dngSpellbook_create(struct dngSpellSlots);

struct dngSpellbook
dngSpellbook_forWizard(struct dngSpellSlots);

void
dngSpellbook_add(struct dngSpellbook *, enum dngSpell_Id, int limit);

bool
dngSpellbook_canCast(const struct dngSpellbook *, enum dngSpell_Id);

void
dngSpellbook_clear(struct dngSpellbook *);

#endif
