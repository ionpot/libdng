#include "chance.h"

#include "die.h"
#include "int-bag.h"

#include <assert.h>
#include <stdbool.h>

typedef struct dngChance T;

T
dngChance_percent(int percent)
{
	return (T){ .percent = percent };
}

void
dngChance_add(T * self, T chance)
{
	assert(self);
	self->percent += chance.percent;
}

bool
dngChance_isSuccess(T self, int rolled)
{
	assert(rolled > 0);
	assert(rolled <= dngChance_MAX.percent);
	return self.percent >= rolled;
}

int
dngChance_roll(struct dngIntBag * bag)
{
	assert(bag);
	return dngDie_roll(dngDie_d100, bag);
}

void
dngChance_sub(T * self, T chance)
{
	assert(self);
	self->percent -= chance.percent;
}
