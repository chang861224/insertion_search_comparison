#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

#include <cstdlib>
#include <cstring>
#include <cstddef>

class SLNode{
    public:
        SLNode(int k, int level);
        void setForward(int idx, SLNode* node);
        int getKey();
        SLNode* getForward(int idx);

    private:
        int key;

        SLNode **forward;
};

class SkipList{
    public:
        SkipList(int max, float p);
        int randomLevel();
        int getLevel();
        SLNode* createSLNode(int key, int level);
        void Insert(int key);
        void Delete(int key);
        void Search(int key);
        int getCopyTimes();

    private:
        int MAXLVL;
        float P;
        int level;
        int copy_times;
        SLNode* header;
};

#endif
