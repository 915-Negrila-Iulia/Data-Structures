#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <cstddef>

#include <iostream>

TComp SortedBag::h(TComp k)
{
	int modulo = k % this->m;
	if (modulo < 0) //for strictly negative modulo
		return modulo + this->m;
	else      //for positive modulo
		return modulo;
}
//theta(1)

bool less_equal(TComp a, TComp b) {
	return bool(a <= b);
}
//theta(1)

bool greater_qual(TComp a, TComp b) {
	return bool(a >= b);
}
//theta(1)

SortedBag::SortedBag(Relation r) {
	//TODO - Implementation
	this->m = 127;
	this->nr_elements = 0;
	this->nodes = new struct Node*[this->m];
	for (int i = 0; i < this->m; i++)
		this->nodes[i] = NULL;
	this->r = r;
}
//theta(m)
//m - number of positions

void SortedBag::resize() {
	
	this->m = this->m * 2;
	TComp* copy_elems = new TComp[this->nr_elements];
	//int copy_elems[1000];

	int k = 0;           // save elements from old hashtabel to copy_elems
	for (int i = 0; i < this->m / 2; i++) {
		struct Node *current_node = this->nodes[i];
		while (current_node != NULL) {
			copy_elems[k] = current_node->info;
			k++;
			current_node = current_node->next;
		}
	}

	// delete the old hash tabel including every element of it
	for (int i = 0; i < this->m / 2; i++) {
		struct Node* current_node = this->nodes[i];
		while (current_node != NULL) {
			struct Node* next_node = current_node->next;
			delete current_node;
			current_node = next_node;
		}
	}
	delete[] this->nodes;
	
	// create a new hash table with double capacity
	this->nr_elements = 0;
	this->nodes = new struct Node* [this->m];
	for (int i = 0; i < this->m; i++)
		this->nodes[i] = NULL;
	
	//rehash
	for (int i = 0; i < k; i++) {
		this->add(copy_elems[i]);
	}
	
	delete[] copy_elems;
}
//theta(n^3/m^2)
//n - number of elements
//m - number of positions
//n/m = average length of SLL

void SortedBag::add(TComp e) {
	//TODO - Implementation
	TComp position = this->h(e);
	auto load_factor = this->nr_elements / this->m;
	
	
	if (load_factor >= 1) {
		resize();
	}
	
	struct Node* new_node = new struct Node;
	new_node->info = e;

	struct Node* current_node = this->nodes[position];
	struct Node* prev_node = NULL;

	while (current_node != NULL && r(e, current_node->info) == false) {
		prev_node = current_node;
		current_node = current_node->next;
	}

	if (prev_node == NULL) {   //add at the beginning
		new_node->next = this->nodes[position];
		this->nodes[position] = new_node;
	}
	else {                    //insert or add at the end
		new_node->next = current_node;
		prev_node->next = new_node;
	}

	this->nr_elements++;
}
//theta(n/m)
//n - number of elements
//m - number of positions
//n/m = average length of SLL


bool SortedBag::remove(TComp e) {
	//TODO - Implementation

	TComp position = this->h(e);

	struct Node* current_node = this->nodes[position];
	struct Node* prev_node = NULL;

	while (current_node != NULL && e != current_node->info) {
		prev_node = current_node;
		current_node = current_node->next;
	}

	if (current_node != NULL) {   //found element
		if (prev_node == NULL) {   //delete head
			this->nodes[position] = this->nodes[position]->next;
		}
		else {                   
			prev_node->next = current_node->next;
		}

		this->nr_elements--;
		return true;
	}
	else  //not found
		return false;
}
//theta(n/m)
//n - number of elements
//m - number of positions
//n/m = average length of SLL

bool SortedBag::search(TComp elem) {
	//TODO - Implementation

	TComp position = this->h(elem);
	struct Node* current_node = this->nodes[position];

	while (current_node != NULL && elem != current_node->info) {
		current_node = current_node->next;
	}

	if (current_node != NULL) {   //found element
		return true;
	}
	else  //not found
		return false;
}
//theta(n/m)
//n - number of elements
//m - number of positions
//n/m = average length of SLL

int SortedBag::nrOccurrences(TComp elem) {
	//TODO - Implementation

	TComp position = this->h(elem);
	struct Node* current_node = this->nodes[position];

	while (current_node != NULL && elem != current_node->info) {
		current_node = current_node->next;
	}

	int count = 0;
	while (current_node != NULL && elem == current_node->info) {
		count++;
		current_node = current_node->next;
	}

	return count;
}
//theta(n/m)
//n - number of elements
//m - number of positions
//n/m = average length of SLL


int SortedBag::size() const {
	//TODO - Implementation
	return this->nr_elements;
}
//theta(1)

bool SortedBag::isEmpty() const {
	//TODO - Implementation
	if (this->nr_elements == 0)
		return true;
	return false;
}
//theta(1);

SortedBagIterator SortedBag::iterator() {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	//TODO - Implementation
	for (int i = 0; i < this->m / 2; i++) {
		struct Node* current_node = this->nodes[i];
		while (current_node != NULL) {
			struct Node* next_node = current_node->next;
			delete current_node;
			current_node = next_node;
		}
	}
	delete[] this->nodes;
}
//theta(n/m)
//n - number of elements
//m - number of positions
//n/m = average length of SLL
