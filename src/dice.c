#include "dice.h"

#include <assert.h>
#include <stdlib.h>

#define NUMBERS_COUNT 300

const struct DNG_Dice
	DNG_Dice_d4 = { .sides = 4 },
	DNG_Dice_d6 = { .sides = 6 },
	DNG_Dice_d8 = { .sides = 8 },
	DNG_Dice_d20 = { .sides = 20 },
	DNG_Dice_d100 = { .sides = 100 };

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
DNG_Dice_init(void)
{
	for (int i = 0; i < NUMBERS_COUNT; ++i)
		numbers[i] = i % 100;

	num_index = 0;
}

struct DNG_Dice_Roll
DNG_Dice_roll(struct DNG_Dice dice)
{
	return (struct DNG_Dice_Roll){
		.result = rollDice(dice.sides),
		.sides = dice.sides
	};
}

struct DNG_Dice_Chance
DNG_Dice_rollChance(int percent)
{
	struct DNG_Dice_Roll roll =
		DNG_Dice_roll(DNG_Dice_d100);

	return (struct DNG_Dice_Chance){
		.success = roll.result <= percent,
		.percent = percent,
		.roll = roll
	};
}
