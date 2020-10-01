#include "int-bag.h"

#include "mempool.h"

#include <assert.h>
#include <stdlib.h>

#define MAX_VALUE dngIntBag_MAX_VALUE
#define REPEAT 3
#define TOTAL ((MAX_VALUE + 1) * REPEAT)

struct dngIntBag {
	int index;
	char contents[TOTAL];
};

typedef struct dngIntBag T;

static void
init(T * self)
{
	assert(self);
	for (int i = 0; i < TOTAL; i++)
		self->contents[i] = i % (MAX_VALUE + 1);
	self->index = 0;
}

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

T *
dngIntBag_create(struct dngMemPool * mem)
{
	assert(mem);
	T * self = dngMemPool_alloc(mem, sizeof(T));
	if (self)
		init(self);
	return self;
}

int
dngIntBag_next(T * self)
{
	assert(self);
	assert(self->index <= TOTAL);
	assert(TOTAL > 0);
	int i = self->index;
	if (i == TOTAL)
		i = 0;
	if (i == 0)
		shuffle(self->contents, TOTAL);
	self->index = i + 1;
	return self->contents[i];
}
