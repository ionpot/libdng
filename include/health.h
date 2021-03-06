#ifndef LIBDNG_HEALTH_H
#define LIBDNG_HEALTH_H

#include "attr.h"

#include <stdbool.h>

struct dngHealth {
	int lost;
	struct dngAttr total;
};

struct dngHealth
dngHealth_fromAttr(struct dngAttr);

struct dngHealth
dngHealth_fromBase(int);

void
dngHealth_gain(struct dngHealth *, int);

int
dngHealth_getRemaining(struct dngHealth);

int
dngHealth_getTotal(struct dngHealth);

bool
dngHealth_hasRemaining(struct dngHealth);

void
dngHealth_lose(struct dngHealth *, int);

void
dngHealth_setBonus(struct dngHealth *, int);

#endif
