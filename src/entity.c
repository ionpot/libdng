#include "entity.h"

#include "attr-primary.h"
#include "class.h"
#include "health.h"

#include <assert.h>
#include <stdbool.h>

static struct dngHealth
toHealth(
	const struct dngAttrPrimary * attr,
	const struct dngClass * klass
) {
	assert(attr);
	assert(klass);

	struct dngHealth health =
		dngHealth_fromAttr(&attr->strength);

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

	struct dngAttrPrimary attr =
		dngAttrPrimary_fromInput(&input->attr);

	const struct dngAttrPrimary_Input * race_bonus =
		dngRace_getBonus(input->race);

	if (race_bonus)
		dngAttrPrimary_addInputToBase(&attr, race_bonus);

	return (struct dngEntity){
		.attr = attr,
		.health = toHealth(&attr, &klass),
		.klass = klass,
		.race = input->race,
		.weapon = input->weapon
	};
}

struct dngAttr
dngEntity_getArmor(const struct dngEntity * entity)
{
	assert(entity);
	return dngAttr_fromBase(0);
}

struct dngAttr
dngEntity_getDodge(const struct dngEntity * entity)
{
	assert(entity);
	return entity->attr.agility;
}

struct dngAttr
dngEntity_getInitiative(const struct dngEntity * entity)
{
	assert(entity);
	const struct dngAttrPrimary * p = &entity->attr;
	return dngAttr_add(p->agility, p->intellect);
}

struct dngAttr
dngEntity_getWill(const struct dngEntity * entity)
{
	assert(entity);
	return entity->attr.intellect;
}

bool
dngEntity_isAlive(const struct dngEntity * entity)
{
	assert(entity);
	return dngHealth_getRemaining(&entity->health) > 0;
}
