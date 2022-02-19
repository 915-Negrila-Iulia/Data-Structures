#include "ShortTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"

#include <iostream>

void my_test() {
	Set s1;
	Set s2;
	for (int i=0; i<10; i++)
		for (int j = 0; j < 3; j++) {
			s1.add(i);
			s1.add(i - 50);
		    s1.add(i + 25);
			s2.add(i);
			s2.add(i + 100);
		}
	s1.intersection(s2);
	for (int i = 0; i < 10; i++) {
		assert(s1.search(i) == true);
		assert(s1.search(i-50) == false);
		assert(s1.search(i+25) == false);
	}
		
}

void testAll() { 
	Set s;
	assert(s.isEmpty() == true);
	assert(s.size() == 0); 
	assert(s.add(5)==true);
	assert(s.add(1)==true);
	assert(s.add(10)==true);
	assert(s.add(7)==true);
	assert(s.add(1)==false);
	assert(s.add(10)==false);
	assert(s.add(-3)==true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);


	SetIterator it = s.iterator();
	it.first();
	int sum = 0;
	while (it.valid()) {
		TElem e = it.getCurrent();
		sum += e;
		it.next();
	}
	assert(sum == 19);

}

