#include "hit-chance.h"

#include "attr.h"
#include "class.h"
#include "entity.h"

#include <assert.h>

struct DNG_HitChance
DNG_HitChance_fromPair(struct DNG_Entity_Pair pair)
{
	assert(pair.source);
	assert(pair.target);
	return (struct DNG_HitChance){
		.source = (struct DNG_HitChance_Source){
			.klass = pair.source->klass
		},
		.target = (struct DNG_HitChance_Target){
			.dodge = pair.target->attr_s.dodge
		}
	};
}

int
DNG_HitChance_getTotal(const struct DNG_HitChance * chance)
{
	assert(chance);
	return DNG_Class_getBonusAttack(&chance->source.klass)
		- DNG_Attr_getTotal(&chance->target.dodge);
}
