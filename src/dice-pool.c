#include "dice-pool.h"

#include "dice.h"
#include "mempool.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#define NODES_PER_ALLOC 5

struct Node {
	struct DNG_DicePool_Roll roll;
	struct Node * next;
};

struct DNG_DicePool {
	struct DNG_MemPool * mempool;
	struct Node * avlb;
	struct Node * used;
	struct Node * used_last;
};

typedef struct DNG_DicePool T;

static struct Node *
allocAvlb(T * self, int amount)
{
	assert(self);
	assert(self->mempool);
	assert(!self->avlb);
	assert(amount > 0);

	size_t size = sizeof(struct Node) * amount;
	struct Node * node =
		DNG_MemPool_alloc(self->mempool, size);

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
DNG_DicePool_create(struct DNG_MemPool * mem)
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
DNG_DicePool_reset(T * self)
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

struct DNG_DicePool_Result
DNG_DicePool_roll(T * self, struct DNG_DicePool_Input input)
{
	assert(self);
	struct Node * node;
	struct DNG_DicePool_Roll * roll = NULL;
	struct DNG_DicePool_Roll * last = NULL;
	int total = 0;

	while (input.count-- > 0) {
		node = nextNode(self);
		if (!node)
			break;
		roll = &node->roll;
		roll->result = DNG_Dice_roll(input.dice).result;
		total += roll->result;
		roll->next = last;
		last = roll;
	}

	return (struct DNG_DicePool_Result){
		.total = total,
		.input = input,
		.roll = roll
	};
}
