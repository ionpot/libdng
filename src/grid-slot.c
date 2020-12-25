#include "grid-slot.h"

#include "entity.h"
#include "grid.h"

#include <assert.h>

typedef struct dngGridSlot T;

T
dngGridSlot_fromPosition(
	const struct dngGrid * grid,
	struct dngGrid_Position pos
) {
	assert(grid);
	return (T){
		.entity = dngGrid_getEntity(grid, pos),
		.position = pos
	};
}
