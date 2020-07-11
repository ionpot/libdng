#ifndef LIBDNG_OUTPUT_H
#define LIBDNG_OUTPUT_H

#include "attack.h"
#include "combat.h"
#include "context.h"
#include "damage.h"
#include "grid.h"

/*
 * attack: entity -> entity
 */
struct DNG_Output_Attack {
	enum DNG_Attack_Result result;
	enum DNG_Attack_Type type;
	struct DNG_Attack_Roll roll;
	struct DNG_Entity_Pair pair;
};

struct DNG_Output_Attack
DNG_Output_doAttack(struct DNG_Context *);

/*
 * we have entered combat
 */
const struct DNG_Combat *
DNG_Output_doCombatBegin(struct DNG_Context *);

/*
 * combat ended
 */
const struct DNG_Combat *
DNG_Output_doCombatEnd(struct DNG_Context *);

/*
 * damage done to an entity
 */
struct DNG_Output_Damage {
	struct DNG_Damage_Roll roll;
	struct DNG_Entity_Pair pair;
};

struct DNG_Output_Damage
DNG_Output_doDamage(struct DNG_Context *);

/*
 * next combat round
 */
int
DNG_Output_doNextRound(struct DNG_Context *);

#endif
