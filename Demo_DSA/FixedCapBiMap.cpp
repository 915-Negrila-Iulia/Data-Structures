#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>

using namespace std;

FixedCapBiMap::FixedCapBiMap(int capacity) {
	//TODO - Implementation
	if (capacity <= 0)
		throw exception("capacity has to be positive integer");
	this->capacity = capacity; 
	this->nr_of_pairs = 0;    
	this->elements = new TElem[capacity];
}
//theta(1)

FixedCapBiMap::~FixedCapBiMap() {
	//TODO - Implementation
	delete[] this->elements;
}
//theta(1)

bool FixedCapBiMap::add(TKey c, TValue v){
	//TODO - Implementation
	if (this->capacity == this->nr_of_pairs)
		throw exception("full capacity");
	int index = 0;
	int count = 0;
	while (count < 2 && index < this->nr_of_pairs) {
		if (this->elements[index].first == c)
			count++;
		index++;
	}
	if (count == 2)
		return false;
	else {
		this->elements[this->nr_of_pairs].first = c;
		this->elements[this->nr_of_pairs].second = v;
		this->nr_of_pairs++;
		return true;
	}
}
//Best Case=theta(1), Worst Case=theta(nr_of_pairs), Total complexity=O(nr_of_pairs)

ValuePair FixedCapBiMap::search(TKey c) const{
	//TODO - Implementation
	int index = 0;
	int count = 0;
	ValuePair pair;
	pair.first = NULL_TVALUE;
	pair.second = NULL_TVALUE;
	while (count < 2 && index < this->nr_of_pairs) {
		if (count == 0 && this->elements[index].first == c) {
			pair.first = this->elements[index].second;
			count++;
		}
			
		else if (count == 1 && this->elements[index].first == c) {
			pair.second = this->elements[index].second;
			count++;
		}
		index++;
	}
	return pair;
}
//Best Case=theta(1), Worst Case=theta(nr_of_pairs), Total complexity=O(nr_of_pairs)

bool FixedCapBiMap::remove(TKey c, TValue v){
	//TODO - Implementation
	int index = 0;
	bool found = false;
	while (not found && index < this->nr_of_pairs) {
		if (this->elements[index].first == c && this->elements[index].second == v)
			found = true;
		else
			index++;
	}
	if (not found)
		return false;
	else {
		this->elements[index] = this->elements[this->nr_of_pairs - 1]; // do not care about order of pairs
		this->nr_of_pairs--;
		return true;
	}
}
//Best Case=theta(1), Worst Case=theta(nr_of_pairs), Total complexity=O(nr_of_pairs)

int FixedCapBiMap::size() const {
	//TODO - Implementation
	return this->nr_of_pairs;
}
//theta(1)

bool FixedCapBiMap::isEmpty() const{
	//TODO - Implementation
	if (this->nr_of_pairs == 0)
		return true;
	else
		return false;
}
//theta(1)

bool FixedCapBiMap::isFull() const {
	//TODO - Implementation
	if (this->nr_of_pairs == this->capacity)
		return true;
	else
		return false;
}
//theta(1)

ValuePair FixedCapBiMap::removeKey(TKey k) {
	ValuePair pair = search(k); //Best Case=theta(1), Worst Case=theta(nr_of_pairs), Total complexity=O(nr_of_pairs)
	if (pair.first != NULL_TVALUE) {
		remove(k, pair.first); //Best Case=theta(1), Worst Case=theta(nr_of_pairs), Total complexity=O(nr_of_pairs)
		if (pair.second != NULL_TVALUE) {
			remove(k, pair.second); //Best Case=theta(1), Worst Case=theta(nr_of_pairs), Total complexity=O(nr_of_pairs)
		}
		else
			remove(k, NULL_TVALUE);
	}
	else{
		remove(k, NULL_TVALUE);
		remove(k, NULL_TVALUE);
	}
	return pair;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}
//theta(1)



