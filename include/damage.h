#ifndef LIBDNG_DAMAGE_H
#define LIBDNG_DAMAGE_H

#include "dice.h"
#include "dice-pool.h"
#include "dice-rolls.h"
#include "entity.h"
#include "source.h"
#include "spell-action.h"
#include "weapon-action.h"

struct dngDamage_Bonus {
	int intellect;
	int strength;
};

struct dngDamage {
	struct dngDice base;
	struct dngDamage_Bonus bonus;
	enum dngSource source;
};

void
dngDamage_apply(int total, struct dngEntity *);

struct dngDamage
dngDamage_ofElectricBolt(struct dngSpellAction);

struct dngDamage
dngDamage_ofElementalBlast(struct dngSpellAction);

struct dngDamage
dngDamage_ofSpell(struct dngSpellAction);

struct dngDamage
dngDamage_ofWeapon(struct dngWeaponAction);

int
dngDamage_getTotal(const struct dngDamage *, const struct dngDiceRolls *);

struct dngDiceRolls *
dngDamage_roll(const struct dngDamage *, struct dngDicePool);

#endif
