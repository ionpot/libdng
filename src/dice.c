#include "dice.h"

#include <assert.h>
#include <stdlib.h>

#define NUMBERS_COUNT 300

const struct dngDice
dngDice_d4 = { .sides = 4 },
dngDice_d6 = { .sides = 6 },
dngDice_d8 = { .sides = 8 },
dngDice_d20 = { .sides = 20 },
dngDice_d100 = { .sides = 100 };

static char numbers[NUMBERS_COUNT];
static int num_index;

static void
shuffle(char * ls, int size)
{
	for (int i = 0; i < size - 1; i++) {
		int j = i + rand() / (RAND_MAX / (size - i) + 1);
		char c = ls[j];
		ls[j] = ls[i];
		ls[i] = c;
	}
}

static int
nextNumber(void)
{
	assert(NUMBERS_COUNT > 0);

	if (num_index >= NUMBERS_COUNT)
		num_index = 0;

	if (num_index == 0)
		shuffle(numbers, NUMBERS_COUNT);

	return numbers[num_index++];
}

static int
rollDice(int sides)
{
	return nextNumber() % sides + 1;
}

void
dngDice_init(void)
{
	for (int i = 0; i < NUMBERS_COUNT; ++i)
		numbers[i] = i % 100;

	num_index = 0;
}

struct dngDice_Roll
dngDice_roll(struct dngDice dice)
{
	return (struct dngDice_Roll){
		.result = rollDice(dice.sides),
		.sides = dice.sides
	};
}

struct dngDice_Chance
dngDice_rollChance(int percent)
{
	struct dngDice_Roll roll =
		dngDice_roll(dngDice_d100);

	return (struct dngDice_Chance){
		.success = roll.result <= percent,
		.percent = percent,
		.roll = roll
	};
}
