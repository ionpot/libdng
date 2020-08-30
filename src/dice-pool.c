#include "dice-pool.h"

#include "dice.h"
#include "mempool.h"
#include "pool.h"

#include <assert.h>
#include <stddef.h>

typedef struct dngDicePool T;

T
dngDicePool_create(struct dngMemPool * mem)
{
	assert(mem);
	return (T){
		.pool = dngPool_create(mem, sizeof(struct dngDicePool_Roll))
	};
}

int
dngDicePool_getTotal(const struct dngDicePool_Roll * roll)
{
	assert(roll);
	int total = 0;
	while (roll) {
		total += roll->result;
		roll = roll->next;
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
		roll = dngPool_next(self.pool);
		if (!roll)
			break;
		roll->result = dngDice_roll(input.dice).result;
		roll->next = last;
		last = roll;
	}

	return roll;
}
