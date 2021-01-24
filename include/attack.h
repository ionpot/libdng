#ifndef LIBDNG_ATTACK_H
#define LIBDNG_ATTACK_H

#include "evasion.h"
#include "hit-chance.h"
#include "int-bag.h"
#include "spell-action.h"
#include "weapon-action.h"

enum dngAttack_Result {
	dngAttack_HIT,
	dngAttack_MISS
};

struct dngAttack_Roll {
	int attack;
	int evasion;
};

struct dngAttack {
	struct dngEvasion evasion;
	struct dngHitChance hit_chance;
};

struct dngAttack
dngAttack_fromSpell(struct dngSpellAction);

struct dngAttack
dngAttack_fromWeapon(struct dngWeaponAction);

enum dngAttack_Result
dngAttack_getResult(const struct dngAttack *, struct dngAttack_Roll);

struct dngAttack_Roll
dngAttack_roll(struct dngIntBag *);

#endif
