#ifndef LIBDNG_SPELL_SLOT_H
#define LIBDNG_SPELL_SLOT_H

#include "spell-id.h"

#include <stdbool.h>

struct dngSpellSlot {
	enum dngSpell_Id id;
	int limit;
	struct dngSpellSlot * next;
	int used;
};

struct dngSpellSlot
dngSpellSlot_create(enum dngSpell_Id, int limit);

void
dngSpellSlot_addLimit(struct dngSpellSlot *, int limit);

bool
dngSpellSlot_canUse(const struct dngSpellSlot *);

void
dngSpellSlot_reset(struct dngSpellSlot *);

void
dngSpellSlot_use(struct dngSpellSlot *);

#endif
