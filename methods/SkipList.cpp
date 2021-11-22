#include "SkipList.h"
using namespace std;

SLNode::SLNode(int k, int level){
    key = k;

    // Allocate memory to forward
    forward = new SLNode* [level+1];

    // Fill forward array with 0(NULL)
    memset(forward, 0, sizeof(SLNode*) * (level+1));
}

void SLNode::setForward(int idx, SLNode* node){
    forward[idx] = node;
}

int SLNode::getKey(){
    return key;
}

SLNode* SLNode::getForward(int idx){
    return forward[idx];
}

SkipList::SkipList(int max, float p){
    MAXLVL = max;
    P = p;
    level = 0;

    // create header node and initialize key to -1
    header = new SLNode(-1, MAXLVL);
}

// create random level for node
int SkipList::randomLevel(){
    float r = (float)rand() / RAND_MAX;
    int lvl = 0;
    
    while(r < P && lvl < MAXLVL){
        lvl++;
        r = (float)rand() / RAND_MAX;
    }

    return lvl;
}

// create new node
SLNode* SkipList::createSLNode(int key, int level){
    SLNode* n = new SLNode(key, level);
    return n;
}

// Insert given key in skip list
void SkipList::Insert(int key){
    SLNode* current = header;

    // create update array and initialize it
    SLNode* update[MAXLVL + 1];
    memset(update, 0, sizeof(SLNode*) * (MAXLVL+1));

    /* start from highest level of skip list
       move the current pointer forward while key
       is greater than key of node next to current
       Otherwise inserted current in update and
       move one level down and continue search
     */
    for(int i = level ; i >= 0 ; i--){
        while(current->getForward(i) != NULL && (current->getForward(i))->getKey() < key)
            current = current->getForward(i);
        update[i] = current;
    }

    /* reached level 0 and forward pointer to
       right, which is desired position to
       insert key.
     */
    current = current->getForward(0);

    /* if current is NULL that means we have reached
       to end of the level or current's key is not equal
       to key to insert that means we have to insert
       node between update[0] and current node */
    if (current == NULL || current->getKey() != key){
        // Generate a random level for node
        int rlevel = randomLevel();

        /* If random level is greater than list's current
           level (node with highest level inserted in
           list so far), initialize update value with pointer
           to header for further use */
        if(rlevel > level){
            for(int i = level + 1 ; i < rlevel + 1 ; i++)
                update[i] = header;

            // Update the list current level
            level = rlevel;
        }

        // create new node with random level generated
        SLNode* n = createSLNode(key, rlevel);

        // insert node by rearranging pointers
        for(int i = 0 ; i <= rlevel ; i++){
            //n->forward[i] = update[i]->forward[i];
            n->setForward(i, update[i]->getForward(i));
            //update[i]->forward[i] = n;
            update[i]->setForward(i, n);
        }
    }
}

// Delete element from skip list
void SkipList::Delete(int key){
    SLNode* current = header;

    // create update array and initialize it
    SLNode* update[MAXLVL + 1];
    memset(update, 0, sizeof(SLNode*) * (MAXLVL + 1));

    /* start from highest level of skip list
       move the current pointer forward while key
       is greater than key of node next to current
       Otherwise inserted current in update and
       move one level down and continue search
     */
    for(int i = level ; i >= 0 ; i--){
        while(current->getForward(i) != NULL && (current->getForward(i))->getKey() < key)
            current = current->getForward(i);
        update[i] = current;
    }

    /* reached level 0 and forward pointer to
       right, which is possibly our desired node.*/
    current = current->getForward(0);

    // If current node is target node
    if(current != NULL and current->getKey() == key){
        /* start from lowest level and rearrange
           pointers just like we do in singly linked list
           to remove target node */
        for(int i = 0 ; i <= level ; i++){
            /* If at level i, next node is not target
               node, break the loop, no need to move
               further level */
            if(update[i]->getForward(i) != current)
                break;

            update[i]->setForward(i, current->getForward(i));
        }

        // Remove levels having no elements
        while(level > 0 && header->getForward(level) == 0)
            level--;
    }
}

// Search for element in skip list
void SkipList::Search(int key){
    SLNode* current = header;

    /* start from highest level of skip list
       move the current pointer forward while key
       is greater than key of node next to current
       Otherwise inserted current in update and
       move one level down and continue search
     */
    for(int i = level ; i >= 0 ; i--){
        while(current->getForward(i) && (current->getForward(i))->getKey() < key)
            current = current->getForward(i);

    }

    /* reached level 0 and advance pointer to
       right, which is possibly our desired node*/
    current = current->getForward(0);
}

