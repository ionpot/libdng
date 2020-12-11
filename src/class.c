#include "class.h"

#include <assert.h>
#include <stdbool.h>

typedef struct dngClass T;

T
dngClass_create(enum dngClass_Id id)
{
	return (T){
		.id = id,
		.level = 1
	};
}

int
dngClass_getAttackBonus(const T * self)
{
	assert(self);
	switch (self->id) {
	case dngClass_FIGHTER:
		return 4 * self->level;
	case dngClass_MAGE:
		return 2 * self->level;
	default:
		assert(false);
	}
}

int
dngClass_getHealthBonus(const T * self)
{
	assert(self);
	switch (self->id) {
	case dngClass_FIGHTER:
		return 4 * self->level;
	case dngClass_MAGE:
		return 2 * self->level;
	}
	assert(false);
}

int
dngClass_getLevel(const T * self, enum dngClass_Id id)
{
	assert(self);
	return (id == self->id) ? self->level : 0;
}

void
dngClass_levelUp(T * self)
{
	assert(self);
	self->level += 1;
}
