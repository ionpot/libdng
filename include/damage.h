#ifndef LIBDNG_DAMAGE_H
#define LIBDNG_DAMAGE_H

#include "dice.h"
#include "dice-pool.h"
#include "dice-rolls.h"
#include "element.h"
#include "entity.h"
#include "source.h"
#include "weapon-id.h"

struct dngDamage_Bonus {
	int intellect;
	int strength;
};

struct dngDamage {
	struct dngDice base;
	struct dngDamage_Bonus bonus;
	enum dngSource source;
};

struct dngDamage
dngDamage_ofElectricBolt(const struct dngEntity *);

struct dngDamage
dngDamage_ofElementalBlast(enum dngElement, const struct dngEntity *);

struct dngDamage
dngDamage_ofEquipped(const struct dngEntity *);

struct dngDamage
dngDamage_ofWeapon(enum dngWeapon_Id, const struct dngEntity *);

int
dngDamage_getTotal(const struct dngDamage *, const struct dngDiceRolls *);

struct dngDiceRolls *
dngDamage_roll(const struct dngDamage *, struct dngDicePool);

#endif
