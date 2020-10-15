#include "entities.h"

#include "entity.h"
#include "mempool.h"
#include "nodes.h"

#include <assert.h>

typedef struct dngEntities T;

T
dngEntities_create(struct dngMemPool * mempool)
{
	assert(mempool);
	return (T){
		.nodes = dngNodes_create(mempool, sizeof(struct dngEntity))
	};
}

struct dngEntity *
dngEntities_next(T self)
{
	return dngNodes_next(self.nodes);
}

void
dngEntities_return(T self, struct dngEntity * entity)
{
	assert(entity);
	dngNodes_return(self.nodes, entity);
}
