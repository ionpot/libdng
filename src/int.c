#include "int.h"

#include "def.h"

#include <assert.h>

void
dngInt_decr(int * i, int amount)
{
	assert(i);
	int x = *i - amount;
	*i = MAX(x, 0);
}
