#ifndef LIBDNG_HIT_CHANCE_H
#define LIBDNG_HIT_CHANCE_H

#include "attr.h"
#include "class.h"
#include "entity.h"

struct DNG_HitChance_Source {
	struct DNG_Class klass;
};

struct DNG_HitChance_Target {
	struct DNG_Attr dodge;
};

struct DNG_HitChance {
	struct DNG_HitChance_Source source;
	struct DNG_HitChance_Target target;
};

struct DNG_HitChance
DNG_HitChance_fromPair(struct DNG_Entity_Pair);

int
DNG_HitChance_getTotal(const struct DNG_HitChance *);

#endif
