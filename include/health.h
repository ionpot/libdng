#ifndef LIBDNG_HEALTH_H
#define LIBDNG_HEALTH_H

#include "attr.h"

#include <stdbool.h>

struct DNG_Health {
	struct DNG_Attr total;
	int lost;
};

struct DNG_Health
DNG_Health_fromBase(int);

void
DNG_Health_gain(struct DNG_Health *, int);

int
DNG_Health_getRemaining(const struct DNG_Health *);

int
DNG_Health_getTotal(const struct DNG_Health *);

bool
DNG_Health_hasRemaining(const struct DNG_Health *);

void
DNG_Health_lose(struct DNG_Health *, int);

#endif
