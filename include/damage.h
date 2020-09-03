#ifndef LIBDNG_DAMAGE_H
#define LIBDNG_DAMAGE_H

enum dngDamage_Type {
	dngDamage_AIR,
	dngDamage_PHYSICAL
};

struct dngDamage_Bonus {
	int intellect;
	int strength;
};

#endif
