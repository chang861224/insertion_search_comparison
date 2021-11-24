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

TNode* Treap::newNode(int key){
    TNode* temp = new TNode(key, rand() % 100);
    temp->setLeft(NULL);
    temp->setRight(NULL);
	return temp;
}

TNode* Treap::rightRotate(TNode* y){
    TNode* x = y->getLeft();
    TNode* T2 = x->getRight();

    x->setRight(y);
    y->setLeft(T2);

	return x;
}

TNode* Treap::leftRotate(TNode* x){
	TNode* y = x->getRight();
    TNode* T2 = y->getLeft();

	y->setLeft(x);
	x->setRight(T2);

	return y;
}

void Treap::Insert(int key){
    root = insertNode(root, key);
}

TNode* Treap::insertNode(TNode* r, int key){
	if (!r)
		return newNode(key);

	if (key <= r->getKey()){
		r->setLeft(insertNode(r->getLeft(), key));

		if ((r->getLeft())->getPriority() > r->getPriority())
			r = rightRotate(r);
	}
	else {
		r->setRight(insertNode(r->getRight(), key));

		if ((r->getRight())->getPriority() > r->getPriority())
			r = leftRotate(r);
	}

	return r;
}

void Treap::Delete(int key){
    root = deleteNode(root, key);
}

TNode* Treap::deleteNode(TNode* r, int key){
	if (r == NULL)
		return r;

	if (key < r->getKey()){
		r->setLeft(deleteNode(r->getLeft(), key));
    }
	else if (key > r->getKey()){
		r->setRight(deleteNode(r->getRight(), key));
    }
	else if (r->getLeft() == NULL){
		TNode* temp = r->getRight();
		delete(r);
		r = temp;
	}
	else if (r->getRight() == NULL){
		TNode* temp = r->getLeft();
		delete(r);
		r = temp;
	}
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

TNode* Treap::searchNode(TNode* r, int key){
	if (r == NULL || r->getKey() == key)
    	return r;

	if (r->getKey() < key)
	    return searchNode(r->getRight(), key);

	return searchNode(r->getLeft(), key);
}

