#ifndef LIBDNG_WEAPON_H
#define LIBDNG_WEAPON_H

#include "dice.h"
#include "int-bag.h"
#include "weapon-id.h"

struct dngDie
dngWeapon_getDie(enum dngWeapon_Id);

int
dngWeapon_getInitiative(enum dngWeapon_Id);

enum dngWeapon_Id
dngWeapon_random(struct dngIntBag *);

#endif
