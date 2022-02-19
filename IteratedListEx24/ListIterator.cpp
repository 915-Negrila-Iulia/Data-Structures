#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>

ListIterator::ListIterator(const IteratedList& list) : list(list) {
	//Done - Implementation
	this->current_element = this->list.head;
}
//Theta(1)

void ListIterator::first() {
	//Done - Implementation
	this->current_element = this->list.head;
}
//Theta(1)

void ListIterator::next() {
	//Done - Implementation
	if (this->current_element == NULL)
		throw std::exception();
	this->current_element = this->current_element->next;
}
//Theta(1)

bool ListIterator::valid() const {
	//Done - Implementation
	if (this->current_element == NULL)
		return false;
	else
		return  true;
}
//Theta(1)

TElem ListIterator::getCurrent() const {
	//Done - Implementation
	if (this->current_element == NULL)
		throw std::exception();
	return this->current_element->info;
}
//Theta(1)

Node* ListIterator::getPos() const {
	if (this->current_element == NULL)
		throw std::exception();
	return this->current_element;
}
//Theta(1)


