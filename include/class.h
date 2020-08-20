#ifndef LIBDNG_CLASS_H
#define LIBDNG_CLASS_H

enum dngClass_Id {
	dngClass_MAGE,
	dngClass_WARRIOR
};

struct dngClass {
	enum dngClass_Id id;
	int level;
};

struct dngClass
dngClass_create(enum dngClass_Id);

int
dngClass_getBonusAttack(const struct dngClass *);

int
dngClass_getBonusHealth(const struct dngClass *);

void
dngClass_levelUp(struct dngClass *);

#endif
