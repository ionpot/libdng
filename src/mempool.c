#include "mempool.h"

#include "def.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

struct Node {
	struct Node * next;
	size_t size;
};

struct Pool {
	struct Pool * next;
};

struct dngMemPool {
	size_t growth_size;
	struct Pool * pools;
	struct Node * avlb;
};

typedef struct dngMemPool T;

static const size_t min_node_size = sizeof(int);
static const size_t min_split_size =
	sizeof(struct Node) + min_node_size;

static struct Node *
addPoolAfter(struct Node ** after, T * self)
{
	assert(after);
	assert(self);

	size_t overhead = sizeof(struct Pool) + sizeof(struct Node);
	struct Pool * pool = malloc(overhead + self->growth_size);
	if (!pool) return NULL;

	pool->next = self->pools;
	self->pools = pool;

	struct Node * node = (void *)(pool + 1);
	node->size = self->growth_size;
	node->next = *after;
	*after = node;
	return node;
}

static struct Node *
findLastAvlb(T * self)
{
	assert(self);
	struct Node * node = self->avlb;
	while (node) {
		if (!node->next) break;
		node = node->next;
	}
	return node;
}

static struct Node *
addPool(T * self)
{
	assert(self);
	struct Node * node = findLastAvlb(self);
	return node
		? addPoolAfter(&node->next, self)
		: addPoolAfter(&self->avlb, self);
}

static struct Node *
splitNode(struct Node * node, size_t by_size)
{
	assert(node);
	assert(node->size >= by_size);

	size_t new_size = node->size - by_size;
	if (new_size < min_split_size)
		return node->next;

	struct Node * new_node =
		(struct Node *)((unsigned char *)(node + 1) + by_size);
	new_node->size = new_size - sizeof(struct Node);
	new_node->next = node->next;

	node->size = by_size;

	return new_node;
}


// public

T *
dngMemPool_create(size_t initial_size)
{
	if (initial_size < min_split_size)
		return NULL;

	size_t overhead = sizeof(T) + sizeof(struct Node);
	T * self = malloc(overhead + initial_size);

	if (!self) return NULL;

	struct Node * node = (void *)(self + 1);
	node->next = NULL;
	node->size = initial_size;

	self->growth_size = initial_size;
	self->pools = NULL;
	self->avlb = node;

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

	size_t size_needed = MAX(request, min_node_size);

	if (size_needed > self->growth_size) {
		struct Node * node = addPool(self);
		return node ? (void *)(node + 1) : NULL;
	}

	struct Node ** next_avlb = &self->avlb;
	struct Node * node = *next_avlb;
	while (node) {
		if (node->size >= size_needed) break;
		next_avlb = &node->next;
		node = *next_avlb;
	}
	if (!node) {
		node = addPoolAfter(next_avlb, self);
		if (!node) return NULL;
	}

	struct Node * avlb = splitNode(node, size_needed);
	*next_avlb = avlb;

	return (void *)(node + 1);
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
