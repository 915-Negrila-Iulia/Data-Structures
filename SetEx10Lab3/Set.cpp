#include "Set.h"
#include "SetITerator.h"
#include <malloc.h>

Set::Set() {
	//TODO - Done
	this->capacity = 10;
	this->nodes = new struct Node[this->capacity];
	this->head = -1;
	this->tail = -1;
	for (int i = 0; i < this->capacity-1; i++)
		this->nodes[i].next = i + 1;
	this->nodes[this->capacity-1].next = -1;
	for (int i = this->capacity - 1; i > 0; i--)
		this->nodes[i].prev = i - 1;
	this->nodes[0].prev = -1;
	this->first_empty = 0;
}
// theta(capacity)

void Set::resize() {
	int new_capacity = this->capacity * 2;
	struct Node* new_nodes = new struct Node[new_capacity];
	
	//move elements to new DLLA:
	for (int i = 0; i < this->capacity; i++) {
		new_nodes[i].info = this->nodes[i].info;
		new_nodes[i].prev = this->nodes[i].prev;
		new_nodes[i].next = this->nodes[i].next;
	}

	//empty positions:
	for (int i = this->capacity; i < new_capacity - 1; i++)
		new_nodes[i].next = i + 1;
	new_nodes[new_capacity - 1].next = -1;
	for (int i = new_capacity - 1; i > this->capacity; i--)
		new_nodes[i].prev = i - 1;
	new_nodes[this->capacity].prev = -1;

	//free nodes of old DLLA
	delete[] this->nodes;

	//change old DLLA with the new resized one:
	this->nodes = new_nodes;
	this->first_empty = this->capacity;
	this->capacity = new_capacity;
}
// theta(capacity)

bool Set::add(TElem elem) {
	//TODO - Done

	//element is already in the set
	if (this->search(elem) == true)
		return false;

	//check if DLLA is full and needs a resize
	if (this->first_empty == -1)
		this->resize();

	//element can be added
	//case when set is empty:
	if (this->head == -1) {
		int new_position = this->first_empty;
		this->nodes[new_position].info = elem;
		this->first_empty = this->nodes[new_position].next;
		this->nodes[new_position].prev = -1;
		this->nodes[new_position].next = -1;
		this->head = new_position;
		this->tail = new_position;
		this->nodes[this->first_empty].prev = -1;
		return true;
	}
	//order is not important in a set. Simply add it at the end:
	int new_position = this->first_empty;
	this->nodes[new_position].info = elem;
	this->nodes[new_position].prev = this->tail;
	this->nodes[this->tail].next = new_position;
	this->tail = new_position;
	this->first_empty = this->nodes[new_position].next;
	this->nodes[new_position].next = -1;

	if (this->first_empty!=-1)
		this->nodes[this->first_empty].prev = -1;
	return true;
}
// BestCase=theta(1), WorstCase=theta(n) amortized, General=O(n)
// n- number of nodes from DLLA (nr elements of set)


bool Set::remove(TElem elem) {
	//TODO - Done

	int current = this->head;

	while (current != -1 && this->nodes[current].info != elem)
		current = this->nodes[current].next;

	//if element exists in the set
	if (current != -1) {

		//if set has only one element
		if (this->head == current && this->tail == current) {
			this->nodes[this->head].prev = -1;
			this->nodes[this->tail].next = -1;
			this->head = -1;
			this->tail = -1;	
		}

		//if element is on the first position of DLLA
		else if (current == this->head) {
			this->head = this->nodes[this->head].next;
			this->nodes[this->head].prev = -1;
		}

		//if element is on last position of DLLA
		else if (current == this->tail) {
			this->tail = this->nodes[this->tail].prev;
			this->nodes[this->tail].next = -1;
		}

		//otherwise
		else {
			int next_elem = this->nodes[current].next;
			int prev_elem = this->nodes[current].prev;
			this->nodes[next_elem].prev = prev_elem;
			this->nodes[prev_elem].next = next_elem;
		}

		//if set if not full and there are empty positions
		if (this->first_empty != -1) {
			this->nodes[this->first_empty].prev = current;
			this->nodes[current].prev = -1;
			this->nodes[current].next = this->first_empty;
			this->first_empty = current;
		}

		//if set if full, having no empty positions
		else {
			this->nodes[current].prev = -1;
			this->nodes[current].next = -1;
			this->first_empty = current;
		}
		return true;
	}

	//if element is not in the set
	else
		return false;
	
}
// BestCase=theta(1), WorstCase=theta(n), General=O(n)
// n- number of nodes from DLLA (nr elements of set)

bool Set::search(TElem elem) const {
	//TODO - Done
	int current = this->head;
	while (current != -1 && this->nodes[current].info != elem)
		current = this->nodes[current].next;

	if (current != -1)
		return true;
	else
		return false;
}
// BestCase=theta(1), WorstCase=theta(n), General=O(n)
// n- number of nodes from DLLA (nr elements of set)

int Set::size() const {
	//TODO - Done
	int count = 0;
	int current = this->head;
	while (current != -1) {
		count++;
		current = this->nodes[current].next;
	}

	return count;
}
// theta(n)
// n- number of nodes from DLLA (nr elements of set)

bool Set::isEmpty() const {
	//TODO - Done
	if (this->head == -1)
		return true;
	else
		return false;
}
// theta(1)

Set::~Set() {
	//TODO - Done
	delete[] this->nodes;
}
// theta(1)


SetIterator Set::iterator() const {
	return SetIterator(*this);
}
// theta(1)

void Set::intersection(const Set& s) {
	
	int current = this->head;
	while (current != -1) {
		if (s.search(this->nodes[current].info) == false) {
			int next_elem = this->nodes[current].next;
			this->remove(this->nodes[current].info);
			current = next_elem;
		}
		else
			current = this->nodes[current].next;
	}
}
// BestCase=theta(n), WorstCase=theta(n*m), General=O(n*m) 
// n- nr elements of this set
// m- nr elements of s set