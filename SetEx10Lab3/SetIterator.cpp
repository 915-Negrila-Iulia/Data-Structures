#include "SetIterator.h"
#include "Set.h"
#include <exception>


SetIterator::SetIterator(const Set& m) : set(m)
{
	//TODO - Done
	this->current = this->set.head;
}
// theta(1)

void SetIterator::first() {
	//TODO - Done
	this->current = this->set.head;
}
// theta(1)

void SetIterator::next() {
	//TODO - Done
	if (this->current == -1)
		throw std::exception();
	this->current = this->set.nodes[this->current].next;
}
// theta(1)

TElem SetIterator::getCurrent()
{
	//TODO - Done
	if (this->current == -1)
		throw std::exception();

	return this->set.nodes[this->current].info;
}
// theta(1)

bool SetIterator::valid() const {
	//TODO - Done
	if (this->current == -1)
		return false;
	else
		return true;
}
// theta(1)


