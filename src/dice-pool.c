#include "dice-pool.h"

#include "die.h"
#include "dice.h"
#include "dice-rolls.h"
#include "int-bag.h"
#include "mempool.h"
#include "pool.h"

#include <assert.h>
#include <stddef.h>

typedef struct dngDicePool T;

T
dngDicePool_create(struct dngMemPool * mem, struct dngIntBag * bag)
{
	assert(mem);
	assert(bag);
	return (T){
		.bag = bag,
		.pool = dngPool_create(mem, sizeof(struct dngDiceRolls))
	};
}

void
dngDicePool_reset(T self)
{
	dngPool_reset(self.pool);
}

struct dngDiceRolls *
dngDicePool_roll(T self, struct dngDice dice)
{
	struct dngDiceRolls * head = NULL;
	struct dngDiceRolls * tail = NULL;
	while (dice.count-- > 0) {
		head = dngPool_next(self.pool);
		if (head) {
			*head = (struct dngDiceRolls){
				.next = tail,
				.result = dngDie_roll(dice.die, self.bag)
			};
			tail = head;
		} else {
			break;
		}
	}
	return tail;
}
