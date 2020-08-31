#include "int.h"

#include <assert.h>

void
dngInt_decr(int * i, int amount)
{
	assert(i);
	int x = *i - amount;
	*i = dngInt_max(x, 0);
}
