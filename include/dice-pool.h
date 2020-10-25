#ifndef LIBDNG_DICEPOOL_H
#define LIBDNG_DICEPOOL_H

#include "attr-primary.h"
#include "dice.h"
#include "entity.h"
#include "element.h"
#include "mempool.h"
#include "pool.h"
#include "spell-slots.h"

#include <stddef.h>

struct dngDicePool_Input {
	int count;
	struct dngDice dice;
};

struct dngDicePool_InputDamage {
	enum dngElement element;
	struct dngDicePool_Input roll;
};

struct dngDicePool_Roll {
	struct dngDicePool_Roll * next;
	int result;
};

struct dngDicePool_AttrRoll {
	struct dngDicePool_Input input;
	struct dngDicePool_Roll * agility;
	struct dngDicePool_Roll * intellect;
	struct dngDicePool_Roll * strength;
};

struct dngDicePool_DamageRoll {
	struct dngDicePool_InputDamage input;
	struct dngDicePool_DamageRoll * next;
	struct dngDicePool_Roll * roll;
};

struct dngDicePool {
	struct dngIntBag * bag;
	struct dngPool * pool;
};

struct dngDicePool
dngDicePool_create(struct dngMemPool *, struct dngIntBag *);

struct dngAttrPrimary_Input
dngDicePool_getAttrPrimaryInput(const struct dngDicePool_AttrRoll *);

int
dngDicePool_getTotal(const struct dngDicePool_Roll *);

int
dngDicePool_getTotalDamage(const struct dngDicePool_DamageRoll *);

void
dngDicePool_reset(struct dngDicePool);

struct dngDicePool_Roll *
dngDicePool_roll(struct dngDicePool, struct dngDicePool_Input);

struct dngDicePool_AttrRoll
dngDicePool_rollAttr(struct dngDicePool);

struct dngDicePool_DamageRoll *
dngDicePool_rollDamage(struct dngDicePool, struct dngDicePool_InputDamage);

struct dngEntity_Input
dngDicePool_rollOrcFighter(struct dngDicePool, struct dngSpellSlots);

#endif
