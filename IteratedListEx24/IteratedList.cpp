
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"

IteratedList::IteratedList() {
	//Done - Implementation
	this->head = NULL;
}
//Theta(1)

int IteratedList::size() const {
	//Done - Implementation
	if (this->head == NULL)
	return 0;

	int size = 0;
	struct Node *current_node; // pointer to a node
	current_node = this->head;
	while (current_node != NULL) {
		size++;
		current_node = current_node->next;
	}

	return size;
}
//Theta(n)

bool IteratedList::isEmpty() const {
	//Done -  Implementation
	if (this->head == NULL)
		return true;
	else
		return false;
}
// Theta(1)

ListIterator IteratedList::first() const {
	return ListIterator(*this);
}
//Theta(1)

TElem IteratedList::getElement(ListIterator pos) const {
	//Done - Implementation
	if (pos.valid() == false)
		throw std::exception();
	return pos.getCurrent();
}
//Theta(1)

TElem IteratedList::remove(ListIterator& pos) {
	//Done - Implementation
	if (pos.valid() == false)
		throw std::exception();

	TElem searched = this->getElement(pos);
	struct Node* prev_node = NULL;
	struct Node* current_node = this->head;

	while (current_node != NULL) {
		if (current_node == pos.getPos()) {
			if (prev_node == NULL)
				this->head = this->head->next;
			else
				prev_node->next = current_node->next;
			delete pos.getPos();
			break;
		}
		else {
			prev_node = current_node;
			current_node = current_node->next;
		}
	}
	pos.next();
	return searched;
}
//BestCase = Theta(1),  WorstCase = Theta(n), Total = O(n)
// n - number of elements from the list

ListIterator IteratedList::search(TElem e) const{
	//Done - Implementation
	ListIterator it = *this;
	bool found = false;
	while (!found && it.valid()) {
		if (it.getCurrent() == e)
			found = true;
		else
			it.next();
	}
	if (found == true) {
		return it;
	}
	else {
		IteratedList ls;
		return ListIterator(ls);
	}
}
//BestCase = Theta(1),  WorstCase = Theta(n), Total = O(n)
// n - number of elements from the list

TElem IteratedList::setElement(ListIterator pos, TElem e) {
    //Done - Implementation
	if (pos.valid() == false)
		throw std::exception();

	TElem searched = this->getElement(pos);
	struct Node* current_node = this->head;

	while (current_node != NULL) {
		if (current_node == pos.getPos()) {
			current_node->info = e;
			break;
		}
		else
			current_node = current_node->next;
	}
	return searched;
}
//BestCase = Theta(1),  WorstCase = Theta(n), Total = O(n)
// n - number of elements from the list

void IteratedList::addToBeginning(TElem e) {
	//Done - implementation
	struct Node *new_node = new struct Node;
	new_node->info = e;
	new_node->next = head;
	head = new_node;
}
//Theta(1)

void IteratedList::addToPosition(ListIterator& pos, TElem e) {
    //Done - Implementation

	if (pos.valid() == false)
		throw std::exception();

	TElem searched = this->getElement(pos);
	struct Node* current_node = this->head;
	struct Node* new_node = new struct Node;
	new_node->info = e;

	while (current_node != NULL) {
		if (current_node == pos.getPos()) {
			new_node->next = current_node->next;
			current_node->next = new_node;
			break;
		}
		else
		current_node = current_node->next;
	}
	pos.next();
}
//BestCase = Theta(1),  WorstCase = Theta(n), Total = O(n)
// n - number of elements from the list

void IteratedList::addToEnd(TElem e) {
	//Done - Implementation

	struct Node* current_node = this->head;
	struct Node* new_node = new struct Node;
	new_node->info = e;

	if (this->head == NULL) {
		new_node->next = NULL;
		this->head = new_node;
	}
	else {

		while (current_node->next != NULL) {
			current_node = current_node->next;
		}

		new_node->next = NULL;
		current_node->next = new_node;
	}
}
//Theta(n)
// n - number of elements from the list

IteratedList::~IteratedList() {
	//TODO - Implementation
	struct Node* current_node = this->head;
	while (current_node != NULL) {
		struct Node* next_node = current_node->next;
		delete current_node;
		current_node = next_node;
	}
}
//Theta(n)
// n - number of elements from the list

void IteratedList::filter(Condition cond) {
	ListIterator it = *this;
	IteratedList ls = IteratedList();
	struct Node* current_node = ls.head;
	while (it.valid()) {
		if (cond(it.getCurrent()) == true)
			//remove(it);
		{
			struct Node* new_node = new struct Node;
			new_node->info = it.getCurrent();
			new_node->next = ls.head;
			ls.head = new_node;
		}
		it.next();
	}
	struct Node* current = this->head;
	while (current != NULL) {
		struct Node* next_node = current->next;
		delete current;
		current = next_node;
	}
	this->head = ls.head;
}
//BestCase = Theta(n^2)
// n - number of elements from the list