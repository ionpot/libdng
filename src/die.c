#include "die.h"

#include "int-bag.h"

#include <assert.h>

typedef struct dngDie T;

int
dngDie_roll(T self, struct dngIntBag * bag)
{
	assert(bag);
	return dngIntBag_next(bag) % self.sides + 1;
}
