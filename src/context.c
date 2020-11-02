#include "context.h"

#include "combat.h"
#include "dice-pool.h"
#include "entities.h"
#include "event-list.h"
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
	self->entities = dngEntities_create(mem);
	if (!self->entities.nodes)
		return NULL;
	self->events = dngEventList_create();
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

void
dngContext_reset(T * self)
{
	assert(self);
	self->events = dngEventList_create();
}
