# Monte Carlo Tree Search
## class MonteCarloTree\<T>
constructor (State state)
```c++
T search(){
        while(this->hasTimeLeft()){
            Node<T>* leaf = this->root->select();
            Node<T>* child = leaf->expand();
            bool result = child->simulate();
            child->backPropagate(result);
        }
        return this->root->bestChild()->state;
    }
```

## class Node\<T>
Needed a State class as it's template class
- state class need to have 
  1. state.getAllPossibleNextState() : returns all the possible state from current state
  2. state.playoutUntilEnd() : returns true or false for who wins with play until ends

## class ChessState
consist of a vector of pieces and a bool value for who's turn it is