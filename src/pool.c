#include "pool.h"

#include "int.h"
#include "mempool.h"

#include <assert.h>
#include <stddef.h>

#define NODES_PER_ALLOC 5

struct Node {
	struct Node * next;
	char content[];
};

struct dngPool {
	struct Node * avlb;
	size_t content_size;
	struct dngMemPool * mempool;
	struct Node * used;
	struct Node * used_last;
};

typedef struct dngPool T;

static struct Node *
allocAvlb(T * self, int node_count)
{
	assert(self);
	assert(self->mempool);
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
		node = (struct Node *)((char *)node + size);
	}

	return last;
}

static struct Node *
avlb2used(T * self)
{
	assert(self);
	assert(self->avlb);

	struct Node * node = self->avlb;

	self->avlb = node->next;
	node->next = self->used;
	self->used = node;

	if (!self->used_last)
		self->used_last = node;

	return node;
}

static struct Node *
nextNode(T * self)
{
	assert(self);

	if (!self->avlb)
		self->avlb = allocAvlb(self, NODES_PER_ALLOC);

	return self->avlb
		? avlb2used(self)
		: NULL;
}

T *
dngPool_create(struct dngMemPool * mem, size_t content_size)
{
	assert(mem);
	assert(content_size > 0);
	T * pool = dngMemPool_alloc(mem, sizeof(T));
	if (!pool)
		return NULL;
	*pool = (T){
		.avlb = NULL,
		.content_size = dngInt_padSize(content_size),
		.mempool = mem,
		.used = NULL,
		.used_last = NULL
	};
	return pool;
}

void *
dngPool_next(T * self)
{
	assert(self);
	struct Node * node = nextNode(self);
	return node
		? node->content
		: NULL;
}

void
dngPool_reset(T * self)
{
	assert(self);
	struct Node * last = self->used_last;
	if (last) {
		last->next = self->avlb;
		self->avlb = self->used;
		self->used = NULL;
		self->used_last = NULL;
	}
}
