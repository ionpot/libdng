#ifndef LIBDNG_STEPS_H
#define LIBDNG_STEPS_H

#include "step-id.h"

struct dngSteps {
	int index;
};

struct dngSteps
dngSteps_create(void);

enum dngStep_Id
dngSteps_get(struct dngSteps);

void
dngSteps_goto(struct dngSteps *, enum dngStep_Id);

enum dngStep_Id
dngSteps_next(enum dngStep_Id);

#endif
