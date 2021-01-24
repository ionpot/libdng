#ifndef LIBDNG_CHANCE_H
#define LIBDNG_CHANCE_H

#include "int-bag.h"

#include <stdbool.h>

#define dngChance_MAX\
	(struct dngChance){.percent = 100}

#define dngChance_ZERO\
	(struct dngChance){.percent = 0}

struct dngChance {
	int percent;
};

struct dngChance
dngChance_percent(int);

void
dngChance_add(struct dngChance *, struct dngChance);

bool
dngChance_isSuccess(struct dngChance, int rolled);

int
dngChance_roll(struct dngIntBag *);

void
dngChance_sub(struct dngChance *, struct dngChance);

#endif
