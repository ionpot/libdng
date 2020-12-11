#ifndef LIBDNG_CLASS_H
#define LIBDNG_CLASS_H

enum dngClass_Id {
	dngClass_FIGHTER,
	dngClass_MAGE
};

struct dngClass {
	enum dngClass_Id id;
	int level;
};

struct dngClass
dngClass_create(enum dngClass_Id);

int
dngClass_getAttackBonus(const struct dngClass *);

int
dngClass_getHealthBonus(const struct dngClass *);

int
dngClass_getLevel(const struct dngClass *, enum dngClass_Id);

void
dngClass_levelUp(struct dngClass *);

#endif
