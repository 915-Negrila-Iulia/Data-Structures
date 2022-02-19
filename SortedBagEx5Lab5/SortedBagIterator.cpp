#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	//TODO - Implementation

	//inorder traversal ->Left Root Right
	struct BSTNode* node = this->bag.root;
	this->s = s;
	this->current_frequency = 1;

	while (node != NULL) {
		this->s.push(node);
		node = node->left;
	}
	if (this->s.isEmpty() == false) {
		this->current_node = this->s.top();
	}
	else
		this->current_node = NULL;

}
//BestCase = theta(1), WorstCase = theta(ht), Overall = O(ht)
//ht - height of the binary search tree

TComp SortedBagIterator::getCurrent() {
	//TODO - Implementation
	if (this->current_node == NULL)
		throw std::exception();
	return this->current_node->pair.info;
}
//theta(1)

bool SortedBagIterator::valid() {
	//TODO - Implementation
	if (this->current_node == NULL)
		return false;
	return true;
}
//theta(1)

void SortedBagIterator::next() {
	//TODO - Implementation
	if (this->current_node == NULL)
		throw std::exception();

	if (this->current_frequency < this->current_node->pair.frequency)
		this->current_frequency++;
	else {
		struct BSTNode* node = this->s.pop();
		this->current_frequency = 1;
		if (node->right != NULL) {
			node = node->right;
			while (node != NULL) {
				this->s.push(node);
				node = node->left;
			}
		}
		if (this->s.isEmpty() == false) {
			this->current_node = this->s.top();
		}
		else
			this->current_node = NULL;
	}
}
//BestCase = theta(1), WorstCase = theta(ht), Overall = O(ht)
//ht - height of the binary search tree

void SortedBagIterator::first() {
	//TODO - Implementation
	struct BSTNode* node = this->bag.root;
	this->current_frequency = 1;
	while (node != NULL) {
		this->s.push(node);
		node = node->left;
	}
	if (this->s.isEmpty() == false) {
		this->current_node = this->s.top();
	}
	else
		this->current_node = NULL;
}
//BestCase = theta(1), WorstCase = theta(ht), Overall = O(ht)
//ht - height of the binary search tree

