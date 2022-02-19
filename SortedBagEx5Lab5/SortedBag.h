#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR
#include <utility>

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

struct TPair {
	TComp info;
	TComp frequency;
};

struct BSTNode {
	TPair pair;
	struct BSTNode* left;
	struct BSTNode* right;
};

class SortedBag {
	friend class SortedBagIterator;

private:
	//TODO - Representation
	struct BSTNode* root;
	Relation r;

public:
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() ;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	BSTNode* find_parent(BSTNode* node);

	BSTNode* find_successor_or_predecessor(BSTNode* node);

	struct BSTNode* find_most_left(BSTNode* node);
	struct BSTNode* find_most_right(BSTNode* root);

	int getRange();

	//destructor
	~SortedBag();
};

class Stack {
private:
	int capacity;
	int length;
	struct BSTNode **nodes;
public:
	Stack();
	void push(BSTNode*);
	struct BSTNode* pop();
	bool isEmpty();
	struct BSTNode* top();

	~Stack();
};