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

struct DNG_Class_Bonus
DNG_Class_getBonus(struct DNG_Class klass)
{
	struct DNG_Class_Bonus bonus;

	switch (klass.id) {
	case DNG_CLASS_MAGE:
		bonus.attack = 2;
		bonus.health = 2;
		break;
	case DNG_CLASS_WARRIOR:
		bonus.attack = 4;
		bonus.health = 4;
		break;
	default:
		assert(false);
	}

	return bonus;
}

void
DNG_Class_levelUp(struct DNG_Class * klass)
{
	assert(klass);
	klass->level += 1;
}
