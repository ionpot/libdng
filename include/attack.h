#ifndef LIBDNG_ATTACK_H
#define LIBDNG_ATTACK_H

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

struct dngAttack
dngAttack_fromPair(struct dngEntity_Pair);

int
dngAttack_getPercent(const struct dngAttack *);

#endif
