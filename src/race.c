#include "race.h"

#include <stddef.h>

static const struct DNG_Race_Bonus
orc_bonus = {
	.strength = 2,
	.intellect = -2
};

const struct DNG_Race_Bonus *
DNG_Race_getBonus(enum DNG_Race_Id id)
{
	switch (id) {
	case DNG_RACE_ORC:
		return &orc_bonus;
	default:
		return NULL;
	}
}

struct DNG_Race_Bonus
DNG_Race_invertBonus(struct DNG_Race_Bonus bonus)
{
	return (struct DNG_Race_Bonus){
		.strength = bonus.strength * -1,
		.intellect = bonus.intellect * -1
	};
}
