#include "source.h"

#include "element.h"

#include <assert.h>
#include <stdbool.h>

enum dngSource
dngSource_fromElement(enum dngElement element)
{
	switch (element) {
	case dngElement_AIR:
		return dngSource_AIR;
	}
	assert(false);
}
