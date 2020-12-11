#include "weapon.h"

#include "die.h"
#include "int-bag.h"
#include "weapon-id.h"

#include <assert.h>
#include <stdbool.h>

static const enum dngWeapon_Id
list[] = {
	dngWeapon_DAGGER,
	dngWeapon_LONG_AXE,
	dngWeapon_STAFF,
	dngWeapon_SWORD
};

static const int list_length =
	sizeof(list) / sizeof(*list);

struct dngDie
dngWeapon_getDie(enum dngWeapon_Id id)
{
	switch (id) {
	case dngWeapon_DAGGER:
		return dngDie_d4;
	case dngWeapon_LONG_AXE:
		return dngDie_d8;
	case dngWeapon_STAFF:
	case dngWeapon_SWORD:
		return dngDie_d6;
	}
	assert(false);
}

int
dngWeapon_getInitiative(enum dngWeapon_Id id)
{
	switch (id) {
	case dngWeapon_DAGGER:
		return 2;
	case dngWeapon_LONG_AXE:
		return -2;
	case dngWeapon_STAFF:
	case dngWeapon_SWORD:
		return 0;
	}
	assert(false);
}

enum dngWeapon_Id
dngWeapon_random(struct dngIntBag * bag)
{
	assert(bag);
	assert(list_length > 0);
	assert(list_length <= dngIntBag_MAX_VALUE + 1);
	return list[dngIntBag_next(bag) % list_length];
}
