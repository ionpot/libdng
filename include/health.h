#ifndef LIBDNG_HEALTH_H
#define LIBDNG_HEALTH_H

#include "attr.h"

struct DNG_Health {
	struct DNG_Attr total;
	int lost;
};

struct DNG_Health
DNG_Health_fromBase(int);

int
DNG_Health_getRemaining(const struct DNG_Health *);

int
DNG_Health_getTotal(const struct DNG_Health *);

#endif
