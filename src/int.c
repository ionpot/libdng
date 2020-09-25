#include "int.h"

#include <assert.h>
#include <stddef.h>

void
dngInt_decr(int * i, int amount)
{
	assert(i);
	int x = *i - amount;
	*i = dngInt_max(x, 0);
}

size_t
dngInt_padSize(size_t input)
{
	assert(input > 0);
	size_t s = sizeof(int);
	size_t r = input % s;
	return input + ((s - r) % s);
}
