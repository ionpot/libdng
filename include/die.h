#ifndef LIBDNG_DIE_H
#define LIBDNG_DIE_H

#include "int-bag.h"

struct dngDie {
	int sides;
};

const struct dngDie
dngDie_d4 = { .sides = 4 },
dngDie_d6 = { .sides = 6 },
dngDie_d8 = { .sides = 8 },
dngDie_d20 = { .sides = 20 },
dngDie_d100 = { .sides = 100 };

int
dngDie_roll(struct dngDie, struct dngIntBag *);

#endif
