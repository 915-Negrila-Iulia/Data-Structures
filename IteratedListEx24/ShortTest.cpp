#include "ShortTest.h"

#include <assert.h>
#include <exception>


#include "IteratedList.h"
#include "ListIterator.h"

#include<iostream>

using namespace std;

bool parity_function(TElem e) {
	if (e % 2 == 0)
		return true;
	else
		return false;
}

bool less100_function(TElem e) {
	if (e < 100)
		return true;
	else
		return false;
}

void my_test() {
	IteratedList list = IteratedList();
	assert(list.size() == 0);
	assert(list.isEmpty());
	for (int i=0; i<3; i++)
		list.addToEnd(100);
	ListIterator it = list.search(100);
	list.addToEnd(20);
	list.addToEnd(99);
	list.addToEnd(250);
	assert(list.size() == 6);
	assert(list.isEmpty()==false);
	Condition function = &parity_function;
	list.filter(function);
	assert(list.size() == 5);
	//list.filter(&less100_function);
	//assert(list.size() == 1);
}

void testAll() {
	IteratedList list = IteratedList();
	assert(list.size() == 0);
	assert(list.isEmpty());

	list.addToEnd(1);
	assert(list.size() == 1);
	assert(!list.isEmpty());

	ListIterator it = list.search(1);
	assert(it.valid());
	assert(it.getCurrent() == 1);
	it.next();
	assert(!it.valid());
	it.first();
	assert(it.valid());
	assert(it.getCurrent() == 1);

	assert(list.remove(it) == 1);
	assert(list.size() == 0);
	assert(list.isEmpty());

	list.addToEnd(1);
	list.addToEnd(3);
	list.addToEnd(7);
	ListIterator it3 = list.first();
	list.addToPosition(it3, 77);
	list.addToPosition(it3, 44);
	assert(list.size() == 5);
	ListIterator it2 = list.first();
	assert(it2.getCurrent() == 1);
	it2.next();
	assert(it2.getCurrent() == 77);
	it2.next();
	assert(it2.getCurrent() == 44);
	it2.next();
	assert(it2.getCurrent() == 3);
	it2.next();
	assert(it2.getCurrent() == 7);
	it2.next();
	assert(it2.valid() == false);

	IteratedList list2 = IteratedList();
	list2.addToBeginning(4);
	list2.addToEnd(5);
	list2.addToBeginning(3);
	list2.addToEnd(6);
	list2.addToBeginning(2);
	list2.addToEnd(7);
	int i = 2;
	ListIterator it4 = list2.first();
	while (it4.valid()) {
		assert(it4.getCurrent() == i);
		i++;
		it4.next();
	}
}


