#include "nodes.h"

#include "int.h"
#include "mempool.h"

#include <assert.h>
#include <stddef.h>

#define NODES_PER_ALLOC 5

struct Node {
	struct Node * next;
	char contents[];
};

struct dngNodes {
	struct Node * avlb;
	size_t content_size;
	struct dngMemPool * mempool;
};

typedef struct dngNodes T;

static struct Node *
allocNewBatch(T * self)
{
	assert(self);
	assert(NODES_PER_ALLOC > 0);
	size_t size = sizeof(struct Node) + self->content_size;
	struct Node * first =
		dngMemPool_alloc(self->mempool, size * NODES_PER_ALLOC);
	if (!first)
		return NULL;
	struct Node * node = first;
	for (int i = NODES_PER_ALLOC - 1; i > 0; i--) {
		node->next = (struct Node *)(node->contents + self->content_size);
		node = node->next;
	}
	node->next = NULL;
	return first;
}

T *
dngNodes_create(struct dngMemPool * mempool, size_t content_size)
{
	assert(mempool);
	assert(content_size > 0);
	T * self = dngMemPool_alloc(mempool, sizeof(T));
	if (!self)
		return NULL;
	self->avlb = NULL;
	self->content_size = dngInt_padSize(content_size);
	self->mempool = mempool;
	return self;
}

void *
dngNodes_next(T * self)
{
	assert(self);
	struct Node * node = self->avlb
		? self->avlb
		: allocNewBatch(self);
	if (node) {
		self->avlb = node->next;
		return node->contents;
	}
	return NULL;
}

void
dngNodes_return(T * self, void * addr)
{
	assert(self);
	assert(addr);
	struct Node * node = (struct Node *)addr - 1;
	node->next = self->avlb;
	self->avlb = node;
}
