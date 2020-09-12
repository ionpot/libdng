#include "int-bag.h"

#include <assert.h>
#include <stdlib.h>

#define MAX_VALUE dngIntBag_MAX_VALUE
#define REPEAT 3
#define TOTAL ((MAX_VALUE + 1) * REPEAT)

static char numbers[TOTAL];
static int num_index;

static void
shuffle(char * ls, int size)
{
	for (int i = 0; i < size - 1; i++) {
		int j = i + rand() / (RAND_MAX / (size - i) + 1);
		char c = ls[j];
		ls[j] = ls[i];
		ls[i] = c;
	}
}

void
dngIntBag_init(void)
{
	for (int i = 0; i < TOTAL; ++i)
		numbers[i] = i % (MAX_VALUE + 1);

	num_index = 0;
}

int
dngIntBag_next(void)
{
	assert(TOTAL > 0);

	if (num_index >= TOTAL)
		num_index = 0;

	if (num_index == 0)
		shuffle(numbers, TOTAL);

	return numbers[num_index++];
}
