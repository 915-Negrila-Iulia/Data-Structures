#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <cstddef>
#include <iostream>

SortedBag::SortedBag(Relation r) {
	//TODO - Implementation
	this->root = NULL;
	this->r = r;
}
//theta(1)

void SortedBag::add(TComp e) {
	//TODO - Implementation

	if (this->root == NULL) {
		struct BSTNode* new_node = new struct BSTNode;
		new_node->pair.info = e;
		new_node->pair.frequency = 1;
		new_node->left = NULL;
		new_node->right = NULL;
		this->root = new_node;
	}

	else {
		bool found = false;
		struct BSTNode* current_node = this->root;
		struct BSTNode* parent_node = NULL;

		while (current_node != NULL && found == false) {
			if (current_node->pair.info == e) {
				//if the element to be added 'e' is already in the sorted bag
				//then we increase its frequency
				found = true;
				current_node->pair.frequency++;
			}
			else if (this->r(e,current_node->pair.info)) {
				parent_node = current_node;
				current_node = current_node->left;
			}
			else {
				parent_node = current_node;
				current_node = current_node->right;
			}
		}

		//if element 'e' is not in the bag
		//then we create a new BTSNode with information = e on the current_node position
		if (found == false) {
			struct BSTNode* new_node = new struct BSTNode;
			new_node->pair.info = e;
			new_node->pair.frequency = 1;
			new_node->left = NULL;
			new_node->right = NULL;
			if (this->r(e, parent_node->pair.info) == true)
				parent_node->left = new_node;
			else
				parent_node->right = new_node;
		}
	}
}
//BestCase = theta(1), WorstCase = theta(ht), Overall = O(ht)
//ht - height of the binary search tree

bool SortedBag::remove(TComp e) {
	//TODO - Implementation

	struct BSTNode* current_node = this->root;
	bool found = false;
	char child;

	while (current_node != NULL && found == false) {
		if (current_node->pair.info == e)
			found = true;
		else if (this->r(e, current_node->pair.info) == true) {
			child = 'l';
			current_node = current_node->left;
		}
		else {
			child = 'r';
			current_node = current_node->right;
		}
	}
	
	if (found == true) {

		if (current_node->pair.frequency > 1)
			current_node->pair.frequency--;

		else {
			//node is a leaf
			if (current_node->right == NULL && current_node->left == NULL) {
				//node is the root
				if (this->root == current_node)
					this->root = NULL;
				//node is a left child
				else if (child == 'l')
					this->find_parent(current_node)->left = NULL;
				//node is a right child
				else
					this->find_parent(current_node)->right = NULL;

				//delete current_node;
			}

			//node has 1 child (left)
			else if (current_node->right == NULL && current_node->left != NULL) {
				if (this->root == current_node)
					this->root = current_node->left;
				else {
					//node is a left child
					if (child == 'l')
						this->find_parent(current_node)->left = current_node->left;
					//node is a right child
					else
						this->find_parent(current_node)->right = current_node->left;
				}
				//delete current_node;
			}

			//node has 1 child (right)
			else if (current_node->right != NULL && current_node->left == NULL) {
				if (this->root == current_node)
					this->root = current_node->right;
				else {
					//node is a left child
					if (child == 'l')
						this->find_parent(current_node)->left = current_node->right;
					//node is a right child
					else
						this->find_parent(current_node)->right = current_node->right;
				}
				//delete current_node;
			}

			//node has 2 children
			else {
				struct BSTNode* successor = this->find_successor_or_predecessor(current_node);
				current_node->pair = successor->pair;
				successor->pair.info = NULL_TCOMP;
				successor->pair.frequency = 0;
				this->remove(successor->pair.info);
				//delete successor;
			}
		}
		return true;
	}
	return false;
}

struct BSTNode* SortedBag::find_parent(BSTNode* node) {
	struct BSTNode* current_node = this->root;
	if (current_node == node)
		return NULL;

	bool found = false;

	while (current_node != NULL && current_node->left != node && current_node->right != node) {
		if (this->r(node->pair.info, current_node->pair.info)==true) {
			current_node = current_node->left;
		}
		else {
			current_node = current_node->right;
		}
	}
	return current_node;

}
//BestCase = theta(1), WorstCase = theta(ht), Overall = O(ht)
//ht - height of the binary search tree

struct BSTNode* SortedBag::find_most_left(BSTNode* root) {
	struct BSTNode* current_node = root;
	while (current_node->left != NULL)
		current_node = current_node->left;
	return current_node;
}
//BestCase = theta(1), WorstCase = theta(ht), Overall = O(ht)
//ht - height of the binary search tree

struct BSTNode* SortedBag::find_most_right(BSTNode* root) {
	struct BSTNode* current_node = root;
	while (current_node->right != NULL)
		current_node = current_node->right;
	return current_node;
}
//BestCase = theta(1), WorstCase = theta(ht), Overall = O(ht)
//ht - height of the binary search tree

struct BSTNode* SortedBag::find_successor_or_predecessor(BSTNode * node) {
	//finding the successor/predecessor of a given node
	//depending on relation r

	//this element does not have successor/predecessor
	if (this->find_most_right(this->root) == node)
		return NULL;

	if (node->right != NULL)
		return this->find_most_left(node->right);
	else {
		if (this->find_parent(node)->left == node)
			return this->find_parent(node);
		else
			return this->find_parent(this->find_parent(node));
	}
	return NULL;
}
//BestCase = theta(1), WorstCase = theta(ht^2), Overall = O(ht^2)
//ht - height of the binary search tree

bool SortedBag::search(TComp elem) const {
	//TODO - Implementation

	struct BSTNode* current_node = this->root;
	bool found = false;

	//searching the element given as parameter
	//if information of a node and the given element respect the
	//given relation 'r', then we check on the left branch (moving to the
	//left child of the node), otherwise we move to the right

	while (current_node != NULL && found==false) {
		if (current_node->pair.info == elem)
			found = true;
		else if (this->r(elem, current_node->pair.info) == true)
			current_node = current_node->left;
		else
			current_node = current_node->right;
	}

	//if the while loop stops because of getting to NULL, then 
	//element was not found

	return found;
}
//BestCase = theta(1), WorstCase = theta(ht), Overall = O(ht)
//ht - height of the binary search tree

int SortedBag::nrOccurrences(TComp elem) const {
	//TODO - Implementation

	struct BSTNode* current_node = this->root;
	int nr_occ = 0;

	while (current_node != NULL && nr_occ==0) {
		if (current_node->pair.info == elem) {
			nr_occ = current_node->pair.frequency;
		}
		else if (this->r(elem, current_node->pair.info) == true)
			current_node = current_node->left;
		else
			current_node = current_node->right;
	}

	return nr_occ;
}
//BestCase = theta(1), WorstCase = theta(ht), Overall = O(ht)
//ht - height of the binary search tree

int SortedBag::size() {
	//TODO - Implementation
	
	int size = 0;

	//preorder traversal (DFT) ->Root Left Right
	struct BSTNode* current_node = this->root;
	Stack s;
	if (current_node != NULL)
		s.push(current_node);
	while (s.isEmpty()==false) {
		current_node = s.pop();
		size += current_node->pair.frequency;
		if (current_node->right != NULL)
			s.push(current_node->right);
		if (current_node->left != NULL)
			s.push(current_node->left);
	}
	return size;
}
//theta(n)
//n - number of nodes


bool SortedBag::isEmpty() const {
	//TODO - Implementation

	if (this->root == NULL)
		return true;
	return false;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	//TODO - Implementation


	struct BSTNode* current_node = this->root;
	Stack s;
	if (current_node != NULL)
		s.push(current_node);
	while (not s.isEmpty()) {
		current_node = s.pop();
		if (current_node->right != NULL)
			s.push(current_node->right);
		if (current_node->left != NULL)
			s.push(current_node->left);
		delete current_node;
	}
	
}
//theta(n)
//n - number of nodes


Stack::Stack() {
	this->capacity = 55555;
	this->length = -1;
	this->nodes = new BSTNode*[this->capacity];
}
//theta(1)

void Stack::push(BSTNode *node) {
	length++;
	this->nodes[length] = node;
}
//theta(1)

struct BSTNode* Stack::pop() {
	struct BSTNode* node = this->nodes[length];
	length--;
	return node;
}
//theta(1)

bool Stack::isEmpty() {
	if (this->length == -1)
		return true;
	return false;
}
//theta(1)

struct BSTNode* Stack::top() {
	struct BSTNode* node = this->nodes[length];
	return node;
}
//theta(1)

Stack::~Stack() {
	delete[] this->nodes;
}
//theta(n)
//n - number of nodes

int SortedBag::getRange() 
{
	if (this->isEmpty())
		return -1;

	int maximum = this->find_most_right(this->root)->pair.info;
	int minimum = this->find_most_left(this->root)->pair.info;

	int difference = maximum - minimum;
	if (difference < 0)
		difference *= -1;

	return difference;
}
//BestCase = theta(1), WorstCase = theta(ht), Overall = O(ht)
//ht - height of the binary search tree