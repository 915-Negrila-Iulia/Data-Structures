#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
#include <stdlib.h>
using namespace std;


Bag::Bag() {
	//Done - Implementation
	this->capacity = 1;
	this->length = 0;
	this->elements = new TElem[this->capacity];
	this->frequencies = new TElem[this->capacity];
}
//theta(1)

void Bag::add(TElem elem) {
	//Done - Implementation
	
	int index = 0;
	bool found = false;
	while (not found && index<this->length) {
		if (this->elements[index] == elem)
			found = true;
		else
			index++;
	}
	if (not found) {

		if (this->capacity == this->length) {

			int new_capacity = this->capacity * 2;
			TElem* new_array = (TElem*)malloc(new_capacity * sizeof(TElem));
			TElem* new_fr = (TElem*)malloc(new_capacity * sizeof(TElem));

			//store the elements from the initial dynamic array in the new array
			for (int i = 0; i < this->length; i++)
			{
				new_array[i] = this->elements[i];
				new_fr[i] = this->frequencies[i];
			}

			//deallocate the memory space for the elements
			free(this->elements);
			free(this->frequencies);

			//resized arrays with double capacity
			this->elements = new_array;
			this->frequencies = new_fr;
			this->capacity = new_capacity;
		}

		this->elements[this->length] = elem;
		this->frequencies[this->length] = 1;
		this->length++;
	}
	else {
		this->frequencies[index]++;
	}
}
//Best Case=theta(1), Worst Case=theta(length), Overall=O(length)

bool Bag::remove(TElem elem) {
	//Done - Implementation
	int index = 0;
	bool found = false;
	while (not found && index< this->length) {
		if (this->elements[index] == elem)
			found = true;
		else
			index++;
	}
	if (not found)
		return false; 
	else {
		if (this->frequencies[index] == 1) {
			this->elements[index] = this->elements[length - 1];
			this->frequencies[index] = this->frequencies[length - 1];
			this->length--;
		}
		else
			this->frequencies[index]--;
		return true;
	}
}
//Best Case=theta(1), Worst Case=theta(length), Overall=O(length)


bool Bag::search(TElem elem) const {
	//Done - Implementation
	for (int i = 0; i < this->length; i++)
		if (this->elements[i] == elem)
			return true;
	return false; 
}
//Best Case=theta(1), Worst Case=theta(length), Overall=O(length)

int Bag::nrOccurrences(TElem elem) const {
	//Done - Implementation
	for (int i = 0; i < this->length; i++)
		if (this->elements[i] == elem)
			return this->frequencies[i];
	return 0;
}
//Best Case=theta(1), Worst Case=theta(length), Overall=O(length)

int Bag::size() const {
	//Done - Implementation
	int number_of_elements = 0;
	for (int i = 0; i < this->length; i++)
		number_of_elements += this->frequencies[i];
	return number_of_elements;
}
//theta(length)

bool Bag::isEmpty() const {
	//Done - Implementation
	if (this->length == 0)
		return true;
	return false;
}
//theta(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
//theta(1)

Bag::~Bag() {
	//Done - Implementation
	delete[] this->elements;
	delete[] this->frequencies;
}
//theta(1)

int Bag::getRange() const {
	if (this->length == 0)
		return -1;
	if (this->length == 1)
		return 0;
	int maxi = this->elements[0];
	int mini = this->elements[0];
	for (int i = 1; i < this->length; i++) {
		if (this->elements[i] < mini)
			mini = this->elements[i];
		if (this->elements[i] > maxi)
			maxi = this->elements[i];
	}
	int diff = maxi - mini;
	return diff;
}
//theta(length)