#include "class.h"

#include <assert.h>
#include <stdbool.h>

struct dngClass
dngClass_create(enum dngClass_Id id)
{
	return (struct dngClass){
		.id = id,
		.level = 1
	};
}

int
dngClass_getAttackBonus(const struct dngClass * klass)
{
	assert(klass);

	switch (klass->id) {
	case dngClass_WARRIOR:
		return 4 * klass->level;
	case dngClass_WIZARD:
		return 2 * klass->level;
	default:
		assert(false);
	}
}

int
dngClass_getHealthBonus(const struct dngClass * klass)
{
	assert(klass);
	switch (klass->id) {
	case dngClass_WARRIOR:
		return 4 * klass->level;
	case dngClass_WIZARD:
		return 2 * klass->level;
	}
	assert(false);
}

void
dngClass_levelUp(struct dngClass * klass)
{
	assert(klass);
	klass->level += 1;
}
