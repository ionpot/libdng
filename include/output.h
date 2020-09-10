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
struct dngOutput_Attack {
	struct dngEntity_Pair pair;
	enum dngAttack_Result result;
	struct dngAttack_Roll roll;
	enum dngAttack_Type type;
};

struct dngOutput_Attack
dngOutput_doAttack(struct dngContext *);

/*
 * we have entered combat
 */
const struct dngCombat *
dngOutput_doCombatBegin(struct dngContext *);

/*
 * combat ended
 */
const struct dngCombat *
dngOutput_doCombatEnd(struct dngContext *);

/*
 * damage done to an entity
 */
struct dngOutput_Damage {
	struct dngEntity_Pair pair;
	struct dngDamage_Roll roll;
};

struct dngOutput_Damage
dngOutput_doDamage(struct dngContext *);

/*
 * next combat round
 */
int
dngOutput_doNextRound(struct dngContext *);

#endif
