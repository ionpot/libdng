#ifndef LIBDNG_DAMAGE_H
#define LIBDNG_DAMAGE_H

#include "attack.h"
#include "dice.h"

enum DNG_Damage_Type {
	DNG_DAMAGE_MAGIC,
	DNG_DAMAGE_PHYSICAL
};

struct DNG_Damage_Bonus {
	int intellect;
	int strength;
};

struct DNG_Damage_Roll {
	enum DNG_Damage_Type type;
	struct DNG_Damage_Bonus bonus;
	struct DNG_Dice_Roll roll;
};

struct DNG_Damage_Roll
DNG_Damage_roll(const struct DNG_Attack_Input *);

int
DNG_Damage_getTotalBonus(const struct DNG_Damage_Bonus *);

int
DNG_Damage_getTotalRoll(const struct DNG_Damage_Roll *);

#endif
