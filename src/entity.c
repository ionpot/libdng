#include "entity.h"

#include "attr-primary.h"
#include "attr-primary-input.h"
#include "class.h"
#include "entity-input.h"
#include "health.h"
#include "spellbook.h"
#include "weapon.h"

#include <assert.h>
#include <stdbool.h>

typedef struct dngEntity T;

static struct dngHealth
toHealth(
	const struct dngAttrPrimary * attr,
	const struct dngClass * klass
) {
	assert(attr);
	assert(klass);

	struct dngHealth health =
		dngHealth_fromAttr(attr->strength);

	int bonus = dngClass_getHealthBonus(klass);

	dngHealth_setBonus(&health, bonus);

	return health;
}

T
dngEntity_fromInput(const struct dngEntityInput * input)
{
	assert(input);

	struct dngClass klass =
		dngClass_create(input->klass);

	struct dngAttrPrimary attr =
		dngAttrPrimary_fromInput(input->attr);

	const struct dngAttrPrimaryInput race_bonus =
		dngRace_getBonus(input->race);

	dngAttrPrimary_addInputToBase(&attr, race_bonus);

	return (T){
		.attr = attr,
		.health = toHealth(&attr, &klass),
		.klass = klass,
		.race = input->race,
		.spellbook = (input->klass == dngClass_MAGE)
			? dngSpellbook_forWizard(input->slots)
			: dngSpellbook_create(input->slots),
		.weapon = input->weapon
	};
}

void
dngEntity_clear(struct dngEntity * self)
{
	assert(self);
	dngSpellbook_clear(&self->spellbook);
}

struct dngAttr
dngEntity_getArmor(const T * self)
{
	assert(self);
	return dngAttr_fromBase(0);
}

int
dngEntity_getClassLevel(const T * self, enum dngClass_Id id)
{
	assert(self);
	return dngClass_getLevel(&self->klass, id);
}

struct dngAttr
dngEntity_getDodge(const T * self)
{
	assert(self);
	return self->attr.agility;
}

struct dngAttr
dngEntity_getInitiative(const T * self)
{
	assert(self);
	const struct dngAttrPrimary * p =
		&self->attr;
	struct dngAttr attr =
		dngAttr_add(p->agility, p->intellect);
	return (struct dngAttr){
		.base = dngAttr_getTotal(attr),
		.bonus = dngWeapon_getInitiative(self->weapon)
	};
}

struct dngAttr
dngEntity_getWill(const T * self)
{
	assert(self);
	return self->attr.intellect;
}

bool
dngEntity_isAlive(const T * self)
{
	assert(self);
	return dngHealth_getRemaining(self->health) > 0;
}
