#ifndef LIBDNG_ATTACK_H
#define LIBDNG_ATTACK_H

#include "dice.h"
#include "entity.h"

enum dngAttack_Result {
	dngAttack_HIT,
	dngAttack_MISS
};

struct dngAttack_Offense {
	struct dngClass klass;
};

struct dngAttack_Defense {
	struct dngAttr armor;
	struct dngAttr dodge;
};

struct dngAttack {
	struct dngAttack_Offense offense;
	struct dngAttack_Defense defense;
};

struct dngAttack_Roll {
	enum dngAttack_Result result;
	int hit_chance;
	struct dngDice_Roll roll;
};

const int dngAttack_base_chance;

struct dngAttack
dngAttack_fromPair(struct dngEntity_Pair);

struct dngAttack_Roll
dngAttack_roll(const struct dngAttack *);

#endif
