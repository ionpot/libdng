#ifndef LIBDNG_HIT_CHANCE_H
#define LIBDNG_HIT_CHANCE_H

#include "attr.h"
#include "class.h"
#include "entity.h"

struct dngHitChance_Source {
	struct dngClass klass;
};

struct dngHitChance_Target {
	struct dngAttr dodge;
};

struct dngHitChance {
	struct dngHitChance_Source source;
	struct dngHitChance_Target target;
};

struct dngHitChance
dngHitChance_fromPair(struct dngEntity_Pair);

int
dngHitChance_getTotal(const struct dngHitChance *);

#endif
