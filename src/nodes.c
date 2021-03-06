#include "nodes.h"

#include "int.h"
#include "mempool.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#define NODES_PER_ALLOC 4

struct Node {
	struct Node * next;
	char contents[];
};

struct dngNodes {
	struct Node * avlb;
	size_t content_size;
	struct dngMemPool * mempool;
	bool no_mem;
};

typedef struct dngNodes T;

static struct Node *
allocNewBatch(T * self, int node_count)
{
	assert(self);
	assert(node_count > 0);
	size_t size = sizeof(struct Node) + self->content_size;
	struct Node * node =
		dngMemPool_alloc(self->mempool, size * node_count);
	if (!node)
		return NULL;
	struct Node * last = NULL;
	while (node_count-- > 0) {
		node->next = last;
		last = node;
		node = (struct Node *)(node->contents + self->content_size);
	}
	return last;
}

T *
dngNodes_create(struct dngMemPool * mempool, size_t content_size)
{
	assert(mempool);
	assert(content_size > 0);
	T * self = dngMemPool_alloc(mempool, sizeof(T));
	if (!self)
		return NULL;
	*self = (T){
		.avlb = NULL,
		.content_size = dngInt_padSize(content_size),
		.mempool = mempool,
		.no_mem = false
	};
	return self;
}

void *
dngNodes_next(T * self)
{
	assert(self);
	struct Node * node = self->avlb
		? self->avlb
		: allocNewBatch(self, NODES_PER_ALLOC);
	self->no_mem = !node;
	if (node) {
		self->avlb = node->next;
		return node->contents;
	}
	return NULL;
}

bool
dngNodes_noMem(const T * self)
{
	assert(self);
	return self->no_mem;
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
