#include "dice-rolls.h"

#include <stddef.h>

typedef struct dngDiceRolls T;

T
dngDiceRolls_make(int result)
{
	return (T){
		.next = NULL,
		.result = result
	};
}

int
dngDiceRolls_getTotal(const T * self)
{
	int total = 0;
	while (self) {
		total += self->result;
		self = self->next;
	}
	return total;
}
