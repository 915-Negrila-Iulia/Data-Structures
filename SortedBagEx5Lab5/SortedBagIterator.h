#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	//TODO - Representation
	Stack s;
	struct BSTNode *current_node;
	TComp current_frequency;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

