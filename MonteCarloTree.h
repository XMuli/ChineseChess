#ifndef MONTECARLOTREE_H
#define MONTECARLOTREE_H

#include "Node.h"


template<class T>
class MonteCarloTree{
public:

    MonteCarloTree(T state)
    {
        root = new Node<T>();
        root->state = state;
    }

    ~MonteCarloTree(){
        delete root;
    }

    T search(){
        while(this->hasTimeLeft()){
            Node<T>* leaf = this->root->select();
            Node<T>* child = leaf->expand();
            bool result = child->simulate();
            child->backPropagate(result);
        }
        return this->root->bestChild()->state;
    }

private:
    int iterateTime = 0;
    bool hasTimeLeft(){
        return ++iterateTime<50;
    }
    Node<T> *root;
};

#endif // MONTECARLOTREE_H
