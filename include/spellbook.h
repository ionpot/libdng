#ifndef LIBDNG_SPELLBOOK_H
#define LIBDNG_SPELLBOOK_H

#include "spell-id.h"
#include "spell-pool.h"
#include "spell-slot.h"

#include <stdbool.h>

struct dngSpellbook {
	struct dngSpellPool pool;
	struct dngSpellSlot * slots;
};

struct dngSpellbook
dngSpellbook_create(struct dngSpellPool);

void
dngSpellbook_add(struct dngSpellbook *, enum dngSpell_Id, int limit);

bool
dngSpellbook_canCast(const struct dngSpellbook *, enum dngSpell_Id);

#endif
