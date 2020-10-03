#include "dice-pool.h"

#include "dice.h"
#include "mempool.h"
#include "pool.h"

#include <assert.h>
#include <stddef.h>

typedef struct dngDicePool T;

union Contents {
	struct dngDicePool_Roll roll;
	struct dngDicePool_DamageRoll damage;
};

T
dngDicePool_create(struct dngMemPool * mem, struct dngIntBag * bag)
{
	assert(mem);
	assert(bag);
	return (T){
		.bag = bag,
		.pool = dngPool_create(mem, sizeof(union Contents))
	};
}

int
dngDicePool_getTotal(const struct dngDicePool_Roll * roll)
{
	int total = 0;
	while (roll) {
		total += roll->result;
		roll = roll->next;
	}
	return total;
}

int
dngDicePool_getTotalDamage(const struct dngDicePool_DamageRoll * damage)
{
	int total = 0;
	while (damage) {
		total += dngDicePool_getTotal(damage->roll);
		damage = damage->next;
	}
	return total;
}

void
dngDicePool_reset(T self)
{
	dngPool_reset(self.pool);
}

struct dngDicePool_Roll *
dngDicePool_roll(T self, struct dngDicePool_Input input)
{
	struct dngDicePool_Roll * roll = NULL;
	struct dngDicePool_Roll * last = NULL;

	while (input.count-- > 0) {
		union Contents * contents =
			dngPool_next(self.pool);
		if (!contents)
			break;
		roll = &contents->roll;
		roll->result = dngDice_roll(input.dice, self.bag).result;
		roll->next = last;
		last = roll;
	}

	return roll;
}

struct dngDicePool_DamageRoll *
dngDicePool_rollDamage(T self, struct dngDicePool_InputDamage input)
{
	struct dngDicePool_DamageRoll * damage = NULL;
	union Contents * contents = dngPool_next(self.pool);
	if (contents) {
		damage = &contents->damage;
		damage->input = input;
		damage->roll = dngDicePool_roll(self, input.roll);
		damage->next = NULL;
	}
	return damage;
}
