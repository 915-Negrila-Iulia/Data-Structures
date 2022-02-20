#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	//Done - Implementation
	//bag is initialized with c
	this->current_index = 0;
	this->current_frequency = 1;
}
//theta(1)

void BagIterator::first() {
	//Done - Implementation
	//reset iterator to the beggining of the container
	this->current_index = 0;
	this->current_frequency = 1;
}
//theta(1)

void BagIterator::next() {
	//Done - Implementation
	//go to the next current element
	if (this->current_index >= this->bag.length)
		throw exception();
	else {
		if (this->current_frequency < this->bag.frequencies[this->current_index])
			this->current_frequency++;
		else {
			this->current_index++;
			this->current_frequency = 1;
		}
	}
}
//theta(1)


bool BagIterator::valid() const {
	//Done - Implementation
	//check if iterator is valid
	if(this->current_index>=this->bag.length)
		return false;
	else
		return true;
}
//theta(1)


TElem BagIterator::getCurrent() const
{
	//Done - Implementation
	if (this->current_index >= this->bag.length)
		throw exception();
	return this->bag.elements[this->current_index];
}
//theta(1)