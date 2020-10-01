#ifndef LIBDNG_ATTR_H
#define LIBDNG_ATTR_H

struct dngAttr {
	int base;
	int bonus;
};

struct dngAttr
dngAttr_fromBase(int);

struct dngAttr
dngAttr_add(struct dngAttr, struct dngAttr);

void
dngAttr_addBase(struct dngAttr *, int);

void
dngAttr_addBonus(struct dngAttr *, int);

int
dngAttr_getTotal(const struct dngAttr *);

void
dngAttr_setBonus(struct dngAttr *, int);

#endif
