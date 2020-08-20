#include "hit-chance.h"

#include "attr.h"
#include "class.h"
#include "entity.h"

#include <assert.h>

struct dngHitChance
dngHitChance_fromPair(struct dngEntity_Pair pair)
{
	assert(pair.source);
	assert(pair.target);
	return (struct dngHitChance){
		.source = (struct dngHitChance_Source){
			.klass = pair.source->klass
		},
		.target = (struct dngHitChance_Target){
			.dodge = pair.target->attr_s.dodge
		}
	};
}

int
dngHitChance_getTotal(const struct dngHitChance * chance)
{
	assert(chance);
	return dngClass_getBonusAttack(&chance->source.klass)
		- dngAttr_getTotal(&chance->target.dodge);
}
