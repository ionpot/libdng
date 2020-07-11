#ifndef LIBDNG_ATTACK_H
#define LIBDNG_ATTACK_H

#include "dice.h"
#include "entity.h"

enum DNG_Attack_Result {
	DNG_ATTACK_HIT,
	DNG_ATTACK_MISS
};

enum DNG_Attack_Type {
	DNG_ATTACK_MAGIC,
	DNG_ATTACK_WEAPON
};

struct DNG_Attack_Bonus {
	int armor;
	int dodge;
	int level;
	int will;
};

struct DNG_Attack_Input {
	enum DNG_Attack_Type type;
	struct DNG_Entity_Pair entities;
};

struct DNG_Attack_Roll {
	struct DNG_Attack_Bonus bonus;
	struct DNG_Dice_Roll roll;
};

struct DNG_Attack_Roll
DNG_Attack_roll(const struct DNG_Attack_Input *);

enum DNG_Attack_Result
DNG_Attack_getResult(const struct DNG_Attack_Roll *);

int
DNG_Attack_getTotalBonus(const struct DNG_Attack_Bonus *);

int
DNG_Attack_getTotalRoll(const struct DNG_Attack_Roll *);

#endif
