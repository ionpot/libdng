#include "context.h"

#include "combat.h"
#include "dice-pool.h"
#include "event.h"
#include "grid.h"
#include "int.h"
#include "int-bag.h"
#include "mempool.h"
#include "spell-slots.h"

#include <assert.h>
#include <stddef.h>

typedef struct dngContext T;

static T *
create(struct dngMemPool * mem)
{
	assert(mem);
	T * self = dngMemPool_alloc(mem, sizeof(T));
	if (!self)
		return NULL;
	self->bag = dngIntBag_create(mem);
	if (!self->bag)
		return NULL;
	self->combat = dngCombat_create(mem, self->bag);
	if (!self->combat)
		return NULL;
	self->dices = dngDicePool_create(mem, self->bag);
	if (!self->dices.pool)
		return NULL;
	self->event = dngEvent_create();
	dngGrid_clear(&self->grid);
	self->mempool = mem;
	self->slots = dngSpellSlots_create(mem);
	if (!self->slots.nodes)
		return NULL;
	return self;
}

T *
dngContext_create(void)
{
	size_t growth_size = dngInt_kib(1);
	struct dngMemPool * mem =
		dngMemPool_create(growth_size);
	if (!mem)
		return NULL;
	T * self = create(mem);
	if (!self)
		dngMemPool_destroy(mem);
	return self;
}

void
dngContext_destroy(T * self)
{
	assert(self);
	dngMemPool_destroy(self->mempool);
}

enum dngEvent_Id
dngContext_nextEvent(T * self)
{
	assert(self);
	enum dngEvent_Id id =
		dngEvent_next(&self->event);
	switch (id) {
	case dngInput_ATTACK:
		if (dngCombat_isTurnOfSide(self->combat, dngGrid_SIDE_A))
			break;
		goto next;
	case dngOutput_COMBAT_END:
		if (dngCombat_hasEnded(self->combat))
			break;
		dngEvent_jump(&self->event, dngOutput_COMBAT_BEGIN);
		goto next;
	case dngOutput_NEXT_ROUND:
		if (dngCombat_isEndOfRound(self->combat))
			break;
		goto next;
	default:
		break;
	}
	return id;
next:
	return dngContext_nextEvent(self);
}

void
dngContext_reset(T * self)
{
	assert(self);
	self->event = dngEvent_create();
}
