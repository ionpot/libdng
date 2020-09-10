#include "entity.h"

#include "attr-primary.h"
#include "attr-secondary.h"
#include "class.h"
#include "health.h"

#include <assert.h>
#include <stdbool.h>

static struct dngHealth
toHealth(
	const struct dngAttrPrimary * attr_p,
	const struct dngClass * klass
) {
	assert(attr_p);
	assert(klass);

	struct dngHealth health =
		dngHealth_fromAttr(&attr_p->strength);

	int bonus = dngClass_getHealthBonus(klass);

	dngHealth_setBonus(&health, bonus);

	return health;
}

struct dngEntity
dngEntity_fromInput(const struct dngEntity_Input * input)
{
	assert(input);

	struct dngClass klass =
		dngClass_create(input->klass);

	struct dngAttrPrimary attr_p =
		dngAttrPrimary_fromInput(&input->attr);

	const struct dngAttrPrimary_Input * race_bonus =
		dngRace_getBonus(input->race);

	if (race_bonus)
		dngAttrPrimary_addInputToBase(&attr_p, race_bonus);

	return (struct dngEntity){
		.attr_p = attr_p,
		.attr_s = dngAttrSecondary_fromPrimary(&attr_p),
		.health = toHealth(&attr_p, &klass),
		.klass = klass,
		.race = input->race,
		.weapon = input->weapon
	};
}

bool
dngEntity_isAlive(const struct dngEntity * entity)
{
	assert(entity);
	return dngHealth_getRemaining(&entity->health) > 0;
}
