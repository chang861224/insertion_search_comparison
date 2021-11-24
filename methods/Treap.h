#ifndef _TREAP_H_
#define _TREAP_H_

#include <cstdlib>
#include <cstddef>

class TNode{
    public:
        // Constructor
        TNode(int k, int p);

        // Get elements
        int getKey();
        int getPriority();

        // Set child
        void setLeft(TNode* node);
        void setRight(TNode* node);

        // Get child
        TNode* getLeft();
        TNode* getRight();

    private:
        int key;
        int priority;
        TNode* left;
        TNode* right;
};

class Treap{
    public:
        // Constructor
        Treap(TNode* r);
        
        // Root
        TNode* getRoot();

        void Insert(int key);
        void Delete(int key);
        TNode* Search(int key);

    private:
        TNode* root;

        TNode* newNode(int key);
        void setRoot(TNode* r);
        TNode* insertNode(TNode* r, int key);
        TNode* deleteNode(TNode* r, int key);
        TNode* searchNode(TNode* r, int key);

        // Rotate
        TNode* rightRotate(TNode* y);
        TNode* leftRotate(TNode* x);
};

#endif

