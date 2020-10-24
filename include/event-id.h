#ifndef LIBDNG_EVENT_ID_H
#define LIBDNG_EVENT_ID_H

enum dngEventId {
	dngInput_ATTACK,
	dngInput_ENTITY,
	dngOutput_ATTACK,
	dngOutput_COMBAT_BEGIN,
	dngOutput_COMBAT_END,
	dngOutput_DAMAGE,
	dngOutput_END,
	dngOutput_NEXT_ROUND
};

#endif