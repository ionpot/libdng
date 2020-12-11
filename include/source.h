#ifndef LIBDNG_SOURCE_H
#define LIBDNG_SOURCE_H

#include "element.h"

enum dngSource {
	dngSource_AIR,
	dngSource_PHYSICAL
};

enum dngSource
dngSource_fromElement(enum dngElement);

#endif
