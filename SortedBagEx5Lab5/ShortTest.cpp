#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <iostream>

bool relation1(TComp e1, TComp e2) {
	if (e1 <= e2)
		return true;
	return false;
}

bool relation12(TComp e1, TComp e2) {
	if (e1 >= e2)
		return true;
	return false;
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
	assert(sb.isEmpty() == true);
	assert(sb.getRange() == -1);

	sb.add(5);
	assert(sb.getRange() == 0);

	sb.add(6);
	sb.add(2);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.getRange() == 8);
	
	sb.add(-5);
	assert(sb.getRange() == 15);


	SortedBag sb1(relation12);
	assert(sb1.isEmpty() == true);
	assert(sb1.getRange() == -1);

	sb1.add(5);
	assert(sb1.getRange() == 0);

	sb1.add(6);
	sb1.add(2);
	sb1.add(5);
	sb1.add(10);
	sb1.add(8);

	assert(sb1.getRange() == 8);

	sb1.add(-5);
	assert(sb1.getRange() == 15);
}
