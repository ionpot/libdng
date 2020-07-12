#ifndef LIBDNG_CLASS_H
#define LIBDNG_CLASS_H

enum DNG_Class_Id {
	DNG_CLASS_MAGE,
	DNG_CLASS_WARRIOR
};

struct DNG_Class {
	enum DNG_Class_Id id;
	int level;
};

struct DNG_Class_Bonus {
	int attack;
	int health;
};

struct DNG_Class
DNG_Class_create(enum DNG_Class_Id);

struct DNG_Class_Bonus
DNG_Class_getBonus(struct DNG_Class);

void
DNG_Class_levelUp(struct DNG_Class *);

#endif
