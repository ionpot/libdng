#include "entity.h"

#include "attr-primary.h"
#include "attr-secondary.h"
#include "class.h"
#include "health.h"

#include <assert.h>
#include <stdbool.h>

static struct DNG_Health
toHealth(
	const struct DNG_AttrPrimary * attr_p,
	const struct DNG_Class * klass
) {
	assert(attr_p);
	assert(klass);

	struct DNG_Health health =
		DNG_Health_fromAttr(&attr_p->strength);

	int bonus = DNG_Class_getBonusHealth(klass);

	DNG_Health_setBonus(&health, bonus);

	return health;
}

struct DNG_Entity
DNG_Entity_fromInput(const struct DNG_Entity_Input * input)
{
	assert(input);

	struct DNG_Class klass =
		DNG_Class_create(input->klass);

	struct DNG_AttrPrimary attr_p =
		DNG_AttrPrimary_fromInput(&input->attr);

	const struct DNG_AttrPrimary_Input * race_bonus =
		DNG_Race_getBonus(input->race);

	if (race_bonus)
		DNG_AttrPrimary_addInputToBase(&attr_p, race_bonus);

	return (struct DNG_Entity){
		.race = input->race,
		.weapon = input->weapon,
		.attr_p = attr_p,
		.attr_s = DNG_AttrSecondary_fromPrimary(&attr_p),
		.klass = klass,
		.health = toHealth(&attr_p, &klass)
	};
}

struct DNG_Entity_HitChance
DNG_Entity_getHitChance(const struct DNG_Entity * entity)
{
	assert(entity);
	return (struct DNG_Entity_HitChance){
		.klass = DNG_Class_getBonusAttack(&entity->klass)
	};
}

bool
DNG_Entity_isAlive(const struct DNG_Entity * entity)
{
	assert(entity);
	return DNG_Health_getRemaining(&entity->health) > 0;
}
