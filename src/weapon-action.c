#include "weapon-action.h"

#include "entity.h"

#include <assert.h>

typedef struct dngWeaponAction T;

T
dngWeaponAction_useEquipped(struct dngEntity_Pair pair)
{
	assert(pair.source);
	return (T){
		.id = pair.source->weapon,
		.target = pair.target,
		.user = pair.source
	};
}
