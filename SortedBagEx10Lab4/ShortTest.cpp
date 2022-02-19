#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <iostream>

#include <exception>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

}

void my_test() {
	SortedBag sb(relation1);
	for (int i = 0; i < 10; i++)
		sb.add(i);

	SortedBagIterator it = sb.iterator();
	it.next();
	it.next();
	assert(it.getCurrent() == 2);
	it.jumpForward(5);
	assert(it.getCurrent() == 7);
	try {
		it.jumpForward(20);
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
}
