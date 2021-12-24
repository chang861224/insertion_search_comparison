#include "Hash.h"

HNode::HNode(int key){
    val = key;
    nextNode = NULL;
}

int HNode::getValue() const{
    return val;
}

HNode* HNode::getNext() const{
    return nextNode;
}

void HNode::setNextNode(HNode* newNode){
    nextNode = newNode;
}

RootNode::RootNode(int key){
    val = key;
    root = NULL;
    nextRoot = NULL;
}

void RootNode::Insert(int key){
    HNode* newNode = new HNode(key);

    if(root == NULL){
        root = newNode;
    }
    else{
        HNode* node = root;

        while(node->getNext() != NULL){
            node = node->getNext();
        }

        node->setNextNode(newNode);
    }
}

void RootNode::setNextRoot(RootNode* node){
    nextRoot = node;
}

int RootNode::getValue() const{
    return val;
}

HNode* RootNode::getRootNode() const{
    return root;
}

RootNode* RootNode::getNextRoot() const{
    return nextRoot;
}

Hash::Hash(){
    do{
        root = rand() % 100000;
    } while(!isPrime(root));
    //std::cout << root << std::endl;

    rootNode = NULL;
}

void Hash::Insert(int key){
    int num = transform(key) % root;
    bool found = false;

    if(rootNode == NULL){
        rootNode = new RootNode(num);
        rootNode->Insert(key);
    }
    else{
        RootNode* target = rootNode;

        while(target != NULL){
            if(target->getValue() == num){
                HNode* last = target->getRootNode();

                while(last->getNext() != NULL){
                    last = last->getNext();
                }

                HNode* newNode = new HNode(key);
                last->setNextNode(newNode);
                found = true;
                break;
            }

            if(target->getNextRoot() != NULL){
                target = target->getNextRoot();
            }
            else{
                break;
            }
        }

        if(!found){
            RootNode* newRoot = new RootNode(num);
            target->setNextRoot(newRoot);
            target = target->getNextRoot();
            target->Insert(key);
        }
    }
}

void Hash::Search(int key){
    int num = transform(key) % root;
    RootNode* r = rootNode;

    while(r != NULL){
        if(r->getValue() == num){
            HNode* node = r->getRootNode();

            while(node != NULL){
                if(node->getValue() == key){
                    //std::cout << "Number found!!" << std::endl;
                    return;
                }

                node = node->getNext();
            }
            
            //std::cout << "Number not found!!" << std::endl;
            return;
        }

        r = r->getNextRoot();
    }

    //std::cout << "Number not found!!" << std::endl;
}

int Hash::transform(int key){
    int n = key;
    int sum = 0;
    int R1 = 1000;
    int R2 = 100;
    int R3 = 10;
    int R4 = 1;

    sum += (R1 * (n % 256));
    n /= 256;
    sum += (R2 * (n % 256));
    n /= 256;
    sum += (R3 * (n % 256));
    n /= 256;
    sum += (R4 * (n % 256));

    return sum;
}

bool Hash::isPrime(int key){
    if(key <= 1){
        return false;
    }

    for(int i = 2 ; i < key ; i++){
        if(key % i == 0){
            return false;
        }
    }

    return true;
}

void Hash::print() const{
    RootNode* r = rootNode;

    while(r != NULL){
        std::cout << r->getValue() << ":";
        HNode* node = r->getRootNode();

        while(node != NULL){
            std::cout << " " << node->getValue();
            node = node->getNext();
        }

        std::cout << std::endl;
        r = r->getNextRoot();
    }
}

