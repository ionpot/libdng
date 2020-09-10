#ifndef LIBDNG_ATTACK_H
#define LIBDNG_ATTACK_H

#include "dice.h"
#include "entity.h"

enum dngAttack_Result {
	dngAttack_HIT,
	dngAttack_MISS
};

struct dngAttack_Bonus {
	int klass;
};

struct dngAttack_Penalty {
	int armor;
	int dodge;
};

struct dngAttack {
	int base;
	struct dngAttack_Bonus bonus;
	struct dngAttack_Penalty penalty;
};

struct dngAttack_Roll {
	int hit_chance;
	enum dngAttack_Result result;
	struct dngDice_Roll roll;
};

struct dngAttack
dngAttack_fromPair(struct dngEntity_Pair);

struct dngAttack_Roll
dngAttack_roll(const struct dngAttack *);

#endif
