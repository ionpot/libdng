#include "mempool.h"

#include "int.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

struct Node {
	struct Node * next;
	size_t size;
	char contents[];
};

struct Pool {
	struct Pool * next;
};

struct dngMemPool {
	struct Node * avlb;
	size_t growth_size;
	struct Pool * pools;
};

typedef struct dngMemPool T;

static const size_t min_node_size =
	sizeof(int);

static struct Node *
extendBy(size_t size, T * self)
{
	assert(self);

	struct Pool * pool = malloc(
		sizeof(struct Pool)
		+ sizeof(struct Node)
		+ size
	);

	if (!pool)
		return NULL;

	struct Pool * prev = self->pools;
	pool->next = prev;
	self->pools = pool;

	struct Node * node = (struct Node *)(pool + 1);
	node->next = NULL;
	node->size = size;

	return node;
}

static struct Node *
splitNode(struct Node * node, size_t by_size)
{
	assert(node);
	assert(node->size >= by_size);

	if (node->size < by_size + sizeof(struct Node) + min_node_size)
		return node->next;

	struct Node * new_node =
		(struct Node *)(node->contents + by_size);
	new_node->size = node->size - by_size - sizeof(struct Node);
	new_node->next = node->next;

	node->size = by_size;

	return new_node;
}

T *
dngMemPool_create(size_t initial_size)
{
	if (initial_size < min_node_size)
		initial_size = min_node_size;

	T * self = malloc(
		sizeof(T)
		+ sizeof(struct Node)
		+ initial_size
	);

	if (!self)
		return NULL;

	struct Node * node = (struct Node *)(self + 1);
	node->next = NULL;
	node->size = initial_size;

	self->avlb = node;
	self->growth_size = initial_size;
	self->pools = NULL;

	return self;
}

void
dngMemPool_destroy(T * self)
{
	assert(self);
	struct Pool * pool = self->pools;
	struct Pool * next;
	while (pool) {
		next = pool->next;
		free(pool);
		pool = next;
	}
	free(self);
}

void *
dngMemPool_alloc(T * self, size_t request)
{
	assert(self);

	size_t size_needed = dngInt_max(request, min_node_size);

	if (size_needed > self->growth_size) {
		struct Node * node = extendBy(size_needed, self);
		return node ? (void *)node->contents : NULL;
	}

	struct Node ** next_avlb = &self->avlb;
	struct Node * node = *next_avlb;
	while (node) {
		if (node->size >= size_needed)
			break;
		next_avlb = &node->next;
		node = *next_avlb;
	}
	if (!node) {
		node = extendBy(self->growth_size, self);
		if (!node)
			return NULL;
	}

	struct Node * avlb = splitNode(node, size_needed);
	*next_avlb = avlb;

	return (void *)node->contents;
}

void
dngMemPool_free(T * self, void * address)
{
	assert(self);
	assert(address);
	struct Node * node = (struct Node *)address - 1;
	node->next = self->avlb;
	self->avlb = node;
}
