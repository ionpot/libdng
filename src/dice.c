#include "dice.h"

#include "die.h"

typedef struct dngDice T;

T
dngDice_of(int count, struct dngDie die)
{
	return (T){
		.count = count,
		.die = die
	};
}
