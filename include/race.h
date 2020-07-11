#ifndef LIBDNG_RACE_H
#define LIBDNG_RACE_H

enum DNG_Race_Id {
	DNG_RACE_HUMAN,
	DNG_RACE_ORC
};

struct DNG_Race_Bonus {
	int strength;
	int intellect;
};

const struct DNG_Race_Bonus *
DNG_Race_getBonus(enum DNG_Race_Id);

struct DNG_Race_Bonus
DNG_Race_invertBonus(struct DNG_Race_Bonus);

#endif
