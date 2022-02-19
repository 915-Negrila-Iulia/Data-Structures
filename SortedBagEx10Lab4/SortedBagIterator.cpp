#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <iostream>

using namespace std;

SortedBagIterator::SortedBagIterator(SortedBag& b) : bag(b) {
	//TODO - Implementation

	//copy elements of the hashtable in array
	this->copy_elems = new TComp[b.nr_elements];
	int k = 0;
	for (int i = 0; i < this->bag.m; i++) {
		struct Node* current_node = this->bag.nodes[i];
		while (current_node != NULL) {
			copy_elems[k] = current_node->info;
			k++;
			current_node = current_node->next;
		}
	}

	//sort array
	for(int i=0; i< this->bag.nr_elements-1; i++)
		for(int j=i+1; j< this->bag.nr_elements; j++)
			if (this->bag.r(copy_elems[i], copy_elems[j]) == false) {
				int aux = copy_elems[i];
				copy_elems[i] = copy_elems[j];
				copy_elems[j] = aux;
			}

	this->copy_current_position = 0;

	//init hash table iterator
	int first_elem = copy_elems[0];
	this->current_position = this->bag.h(first_elem);

	//all SLLs are sorted =>
	this->current_element = this->bag.nodes[this->current_position];
	
}
//theta(n^3/m)
//n - number of elements
//m - number of positions
//n/m = average length of SLL

TComp SortedBagIterator::getCurrent() {
	//TODO - Implementation
	if (this->copy_current_position == this->bag.nr_elements)
		throw std::exception();
	
	this->current_position = this->bag.h(copy_elems[copy_current_position]);
	struct Node* current_node = this->bag.nodes[this->current_position];

	while (current_node != NULL && copy_elems[copy_current_position] != current_node->info) {
		current_node = current_node->next;
	}
	this->current_element = current_node;

	return this->current_element->info;
}
//BC=theta(1), WC=theta(n/m), Overall=O(n/m)
//n - number of elements
//m - number of positions
//n/m = average length of SLL

bool SortedBagIterator::valid() {
	//TODO - Implementation
	if (this->copy_current_position == this->bag.nr_elements)
		return false;
	return true;
}
//theta(1)

void SortedBagIterator::next() {
	//TODO - Implementation
	if (this->copy_current_position == this->bag.nr_elements)
		throw std::exception();

	this->copy_current_position++;

	if (copy_elems[copy_current_position] == copy_elems[copy_current_position-1])
		this->current_element = this->current_element->next;
	else {
		
		this->current_position = this->bag.h(copy_elems[copy_current_position]);
		struct Node* current_node = this->bag.nodes[this->current_position];

		while (current_node != NULL && copy_elems[copy_current_position] != current_node->info) {
			current_node = current_node->next;
		}
		this->current_element = current_node;
	}
}
//BC=theta(1), WC=theta(n/m), Overall=O(n/m)
//n - number of elements
//m - number of positions
//n/m = average length of SLL

void SortedBagIterator::first() {
	//TODO - Implementation
	this->copy_current_position = 0;

	int first_elem = copy_elems[0];
	this->current_position = first_elem % this->bag.m;

	this->current_element = this->bag.nodes[this->current_position];
}

void SortedBagIterator::jumpForward(int k)
{
	if (this->copy_current_position + k >= this->bag.size()) //there are not k posititions forword from the current one
	{
		this->copy_current_position = this->bag.nr_elements; //make iterator invalid
		throw std::exception();
	}
	else if (k <= 0)
		throw std::exception();
	else {
		while (k != 0) {
			this->next();
			k--;
		}
	}
}
//BC=theta(1), WC=theta(n/m), Overall=O(n/m)
//n - number of elements
//m - number of positions
//n/m = average length of SLL



