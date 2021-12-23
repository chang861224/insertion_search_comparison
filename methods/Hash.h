#ifndef _HEAP_H_
#define _HEAP_H_

#include <iostream>
#include <cstdlib>
#include <cstddef>

class HNode{
    public:
        HNode(int key);
        int getValue() const;
        HNode* getNext() const;
        void setNextNode(HNode* newNode);

    private:
        int val;
        HNode* nextNode;
};

class RootNode{
    public:
        RootNode(int key);
        void Insert(int key);
        void setNextRoot(RootNode* node);
        int getValue() const;
        HNode* getRootNode() const;
        RootNode* getNextRoot() const;

    private:
        int val;
        HNode* root;
        RootNode* nextRoot;
};

class Hash{
    public:
        Hash();
        void Insert(int key);
        void Search(int key);
        void print() const;

    private:
        int transform(int key);
        bool isPrime(int key);

        int root;
        RootNode* rootNode;
};

#endif
