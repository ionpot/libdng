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
	enum dngAttack_Result result;
	enum dngAttack_Type type;
	struct dngAttack_Roll roll;
	struct dngEntity_Pair pair;
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
	struct dngDamage_Roll roll;
	struct dngEntity_Pair pair;
};

struct dngOutput_Damage
dngOutput_doDamage(struct dngContext *);

/*
 * next combat round
 */
int
dngOutput_doNextRound(struct dngContext *);

#endif
