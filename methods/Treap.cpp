#include "Treap.h"

TNode::TNode(int k, int p){
    key = k;
    priority = p;
}

int TNode::getKey(){
    return key;
}

int TNode::getPriority(){
    return priority;
}

void TNode::setLeft(TNode* node){
    left = node;
}

void TNode::setRight(TNode* node){
    right = node;
}

TNode* TNode::getLeft(){
    return left;
}

TNode* TNode::getRight(){
    return right;
}

Treap::Treap(TNode* r){
    root = r;
}

void Treap::setRoot(TNode* r){
    root = r;
}

TNode* Treap::getRoot(){
    return root;
}

/* Utility function to add a new key */
TNode* Treap::newNode(int key){
    TNode* temp = new TNode(key, rand() % 100);
    temp->setLeft(NULL);
    temp->setRight(NULL);
	return temp;
}

// A utility function to right rotate subtree rooted with y
TNode* Treap::rightRotate(TNode* y){
    TNode* x = y->getLeft();
    TNode* T2 = x->getRight();

	// Perform rotation
    x->setRight(y);
    y->setLeft(T2);

	// Return new root
	return x;
}

// A utility function to left rotate subtree rooted with x
TNode* Treap::leftRotate(TNode* x){
	TNode* y = x->getRight();
    TNode* T2 = y->getLeft();

	// Perform rotation
	y->setLeft(x);
	x->setRight(T2);

	// Return new root
	return y;
}

void Treap::Insert(int key){
    root = insertNode(root, key);
}

/* Recursive implementation of insertion in Treap */
TNode* Treap::insertNode(TNode* r, int key){
	// If root is NULL, create a new node and return it
	if (!r)
		return newNode(key);

	// If key is smaller than root
	if (key <= r->getKey()){
		// insertNode in left subtree
		r->setLeft(insertNode(r->getLeft(), key));

		// Fix Heap property if it is violated
		if ((r->getLeft())->getPriority() > r->getPriority())
			r = rightRotate(r);
	}
	else {// If key is greater{
		// Insert in right subtree
		r->setRight(insertNode(r->getRight(), key));

		// Fix Heap property if it is violated
		if ((r->getRight())->getPriority() > r->getPriority())
			r = leftRotate(r);
	}

	return r;
}

void Treap::Delete(int key){
    root = deleteNode(root, key);
}

/* Recursive implementation of Delete() */
TNode* Treap::deleteNode(TNode* r, int key){
	if (r == NULL)
		return r;

	if (key < r->getKey())
		r->setLeft(deleteNode(r->getLeft(), key));
	else if (key > r->getKey())
		r->setRight(deleteNode(r->getRight(), key));

	// IF KEY IS AT ROOT

	// If left is NULL
	else if (r->getLeft() == NULL){
		TNode* temp = r->getRight();
		delete(r);
		r = temp; // Make right child as root
	}

	// If Right is NULL
	else if (r->getRight() == NULL){
		TNode* temp = r->getLeft();
		delete(r);
		r = temp; // Make left child as root
	}

	// If ksy is at root and both left and right are not NULL
	else if ((r->getLeft())->getPriority() < (r->getRight())->getPriority()){
		r = leftRotate(r);
		r->setLeft(deleteNode(r->getLeft(), key));
	}
	else{
		r = rightRotate(r);
		r->setRight(deleteNode(r->getRight(), key));
	}

	return r;
}

TNode* Treap::Search(int key){
    return searchNode(root, key);
}

// C function to search a given key in a given BST
TNode* Treap::searchNode(TNode* r, int key){
	// Base Cases: root is null or key is present at root
	if (r == NULL || r->getKey() == key)
    	return r;

	// Key is greater than root's key
	if (r->getKey() < key)
	    return searchNode(r->getRight(), key);

	// Key is smaller than root's key
	return searchNode(r->getLeft(), key);
}

