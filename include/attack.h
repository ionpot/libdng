#ifndef LIBDNG_ATTACK_H
#define LIBDNG_ATTACK_H

#include "dice.h"
#include "entity.h"

enum dngAttack_Result {
	dngAttack_HIT,
	dngAttack_MISS
};

enum dngAttack_Type {
	dngAttack_MAGIC,
	dngAttack_WEAPON
};

struct dngAttack_Bonus {
	int armor;
	int dodge;
	int level;
	int will;
};

struct dngAttack_Input {
	enum dngAttack_Type type;
	struct dngEntity_Pair entities;
};

struct dngAttack_Roll {
	struct dngAttack_Bonus bonus;
	struct dngDice_Roll roll;
};

struct dngAttack_Roll
dngAttack_roll(const struct dngAttack_Input *);

enum dngAttack_Result
dngAttack_getResult(const struct dngAttack_Roll *);

int
dngAttack_getTotalBonus(const struct dngAttack_Bonus *);

int
dngAttack_getTotalRoll(const struct dngAttack_Roll *);

#endif
