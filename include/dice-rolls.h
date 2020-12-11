#ifndef LIBDNG_DICE_ROLLS_H
#define LIBDNG_DICE_ROLLS_H

struct dngDiceRolls {
	struct dngDiceRolls * next;
	int result;
};

struct dngDiceRolls
dngDiceRolls_make(int result);

int
dngDiceRolls_getTotal(const struct dngDiceRolls *);

#endif
