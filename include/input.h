#ifndef LIBDNG_INPUT_H
#define LIBDNG_INPUT_H

#include "context.h"
#include "input-def.h"

void
dngInput_forAttack(struct dngContext *, struct dngInput_Attack);

void
dngInput_forEntity(struct dngContext *, struct dngInput_NewEntity);

#endif
