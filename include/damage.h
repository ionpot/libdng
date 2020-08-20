#ifndef LIBDNG_DAMAGE_H
#define LIBDNG_DAMAGE_H

#include "attack.h"
#include "dice.h"

enum dngDamage_Type {
	dngDamage_MAGIC,
	dngDamage_PHYSICAL
};

struct dngDamage_Bonus {
	int intellect;
	int strength;
};

struct dngDamage_Roll {
	enum dngDamage_Type type;
	struct dngDamage_Bonus bonus;
	struct dngDice_Roll roll;
};

struct dngDamage_Roll
dngDamage_roll(const struct dngAttack_Input *);

int
dngDamage_getTotalBonus(const struct dngDamage_Bonus *);

int
dngDamage_getTotalRoll(const struct dngDamage_Roll *);

#endif
