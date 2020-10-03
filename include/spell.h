#ifndef LIBDNG_SPELL_H
#define LIBDNG_SPELL_H

#include "attr.h"
#include "class.h"
#include "dice-pool.h"
#include "element.h"

struct dngSpell_Damage {
	struct dngDicePool_DamageRoll * base;
	int intellect;
	struct dngDicePool_DamageRoll * level;
};

int
dngSpell_getTotalDamage(const struct dngSpell_Damage *);

struct dngSpell_Damage
dngSpell_rollElectricBolt(struct dngDicePool, struct dngClass);

struct dngSpell_Damage
dngSpell_rollElementalBlast(struct dngDicePool, enum dngElement, struct dngAttr);

#endif
