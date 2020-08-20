#include "dice-pool.h"

#include "dice.h"
#include "mempool.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#define NODES_PER_ALLOC 5

struct Node {
	struct dngDicePool_Roll roll;
	struct Node * next;
};

struct dngDicePool {
	struct dngMemPool * mempool;
	struct Node * avlb;
	struct Node * used;
	struct Node * used_last;
};

typedef struct dngDicePool T;

static struct Node *
allocAvlb(T * self, int amount)
{
	assert(self);
	assert(self->mempool);
	assert(!self->avlb);
	assert(amount > 0);

	size_t size = sizeof(struct Node) * amount;
	struct Node * node =
		dngMemPool_alloc(self->mempool, size);

	if (!node)
		return NULL;

	struct Node * last = NULL;

	for (int i = amount - 1; i > 0; --i) {
		node[i].next = last;
		last = node + i;
	}

	return node;
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

T
dngDicePool_create(struct dngMemPool * mem)
{
	assert(mem);
	return (T){
		.avlb = NULL,
		.used = NULL,
		.used_last = NULL,
		.mempool = mem
	};
}

void
dngDicePool_reset(T * self)
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

struct dngDicePool_Result
dngDicePool_roll(T * self, struct dngDicePool_Input input)
{
	assert(self);
	struct Node * node;
	struct dngDicePool_Roll * roll = NULL;
	struct dngDicePool_Roll * last = NULL;
	int total = 0;

	while (input.count-- > 0) {
		node = nextNode(self);
		if (!node)
			break;
		roll = &node->roll;
		roll->result = dngDice_roll(input.dice).result;
		total += roll->result;
		roll->next = last;
		last = roll;
	}

	return (struct dngDicePool_Result){
		.total = total,
		.input = input,
		.roll = roll
	};
}
