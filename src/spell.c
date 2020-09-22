#include "spell.h"

#include "attr.h"
#include "class.h"
#include "dice-pool.h"
#include "element.h"

#include <assert.h>

int
dngSpell_getTotalDamage(const struct dngSpell_Damage * dmg)
{
	assert(dmg);
	int total = dmg->intellect;
	total += dngDicePool_getTotalDamage(dmg->base);
	total += dngDicePool_getTotalDamage(dmg->level);
	return total;
}

struct dngSpell_Damage
dngSpell_rollElectricBolt(struct dngDicePool pool, struct dngClass klass)
{
	struct dngDicePool_InputDamage input = {
		.element = dngElement_AIR,
		.roll = (struct dngDicePool_Input){
			.count = 2,
			.dice = dngDice_d8
		}
	};
	struct dngDicePool_RollDamage * base =
		dngDicePool_rollDamage(pool, input);

	input.roll.count = klass.level;
	struct dngDicePool_RollDamage * level =
		dngDicePool_rollDamage(pool, input);

	return (struct dngSpell_Damage){
		.base = base,
		.intellect = 0,
		.level = level
	};
}

struct dngSpell_Damage
dngSpell_rollElementalBlast(
	struct dngDicePool pool,
	enum dngElement element,
	struct dngAttr intellect
) {
	struct dngDicePool_InputDamage input = {
		.element = element,
		.roll = (struct dngDicePool_Input){
			.count = 1,
			.dice = dngDice_d4
		}
	};
	return (struct dngSpell_Damage){
		.base = dngDicePool_rollDamage(pool, input),
		.intellect = dngAttr_getTotal(&intellect),
		.level = NULL
	};
}
