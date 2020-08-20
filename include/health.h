#ifndef LIBDNG_HEALTH_H
#define LIBDNG_HEALTH_H

#include "attr.h"

#include <stdbool.h>

struct dngHealth {
	struct dngAttr total;
	int lost;
};

struct dngHealth
dngHealth_fromAttr(const struct dngAttr *);

struct dngHealth
dngHealth_fromBase(int);

void
dngHealth_gain(struct dngHealth *, int);

int
dngHealth_getRemaining(const struct dngHealth *);

int
dngHealth_getTotal(const struct dngHealth *);

bool
dngHealth_hasRemaining(const struct dngHealth *);

void
dngHealth_lose(struct dngHealth *, int);

void
dngHealth_setBonus(struct dngHealth *, int);

#endif
