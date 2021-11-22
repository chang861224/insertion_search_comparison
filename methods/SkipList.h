// C++ code for inserting element in skip list
#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

#include <bits/stdc++.h>

// Class to implement node
class SLNode{
    public:
        SLNode(int k, int level);
        void setForward(int idx, SLNode* node);
        int getKey();
        SLNode* getForward(int idx);

    private:
        int key;

        // Array to hold pointers to node of different level
        SLNode **forward;
};

class SkipList{
    public:
        SkipList(int max, float p);
        int randomLevel();
        SLNode* createSLNode(int key, int level);
        void insertElement(int key);
        void deleteElement(int key);
        void searchElement(int key);
        void displayList();

    private:
        // Maximum level for this skip list
        int MAXLVL;

        // P is the fraction of the nodes with level
        // i pointers also having level i+1 pointers
        float P;

        // current level of skip list
        int level;

        // pointer to header node
        SLNode* header;
};

#endif
