#ifndef MONTECARLOTREE_H
#define MONTECARLOTREE_H

#include "Node.h"

namespace utils {
    bool hasTimeLeft(){
        return true;
    }
}

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
        while(utils::hasTimeLeft()){
            Node<T>* leaf = this->root->select();
            Node<T>* child = leaf->expand();
            bool result = child->simulate();
            child->backPropagate(result);
        }
        return this->root->bestChild()->state;
    }

private:
    Node<T> *root;
};

#endif // MONTECARLOTREE_H
