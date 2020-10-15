#ifndef LIBDNG_ENTITIES_H
#define LIBDNG_ENTITIES_H

#include "entity.h"
#include "mempool.h"
#include "nodes.h"

struct dngEntities {
	struct dngNodes * nodes;
};

struct dngEntities
dngEntities_create(struct dngMemPool *);

struct dngEntity *
dngEntities_next(struct dngEntities);

void
dngEntities_return(struct dngEntities, struct dngEntity *);

#endif
