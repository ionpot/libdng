#include "class.h"

#include <assert.h>
#include <stdbool.h>

struct DNG_Class
DNG_Class_create(enum DNG_Class_Id id)
{
	return (struct DNG_Class){
		.id = id,
		.level = 1
	};
}

int
DNG_Class_getBonusAttack(const struct DNG_Class * klass)
{
	assert(klass);

	switch (klass->id) {
	case DNG_CLASS_MAGE:
		return 2 * klass->level;
	case DNG_CLASS_WARRIOR:
		return 4 * klass->level;
	default:
		assert(false);
	}
}

int
DNG_Class_getBonusHealth(const struct DNG_Class * klass)
{
	assert(klass);

	switch (klass->id) {
	case DNG_CLASS_MAGE:
		return 2 * klass->level;
	case DNG_CLASS_WARRIOR:
		return 4 * klass->level;
	default:
		assert(false);
	}
}

void
DNG_Class_levelUp(struct DNG_Class * klass)
{
	assert(klass);
	klass->level += 1;
}
