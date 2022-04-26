//
// Created by Daniel on 4/20/2022.
//


#ifndef DATA_STRUCTURES_234218_NODE_H
#define DATA_STRUCTURES_234218_NODE_H

#include "Pair.h"

template<class T, class Key>
class Node {
public:
    int h_left;
    int h_right;
    int balance_factor;
    Pair<T, Key> pair;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> father;

    Node(std::shared_ptr<Node<T, Key>> left, std::shared_ptr<Node<T, Key>> right, std::shared_ptr<Node<T, Key>> father,
         Pair<T, Key> pair);

    void UpdateBalanceFactor() {
        if (this->left == NULL)
            h_left = 0;
        else
            h_left = std::max(left->h_left, left->h_right) + 1;
        if (this->right == NULL)
            h_right = 0;
        else
            h_right = std::max(right->h_right, right->h_left) + 1;
        balance_factor = h_left - h_right;
    }
};

template<class T, class Key>
Node<T, Key>::Node(std::shared_ptr<Node<T, Key>> left, std::shared_ptr<Node<T, Key>> right,
                   std::shared_ptr<Node<T, Key>> father, Pair<T, Key> pair):

        left(left), right(right), father(father), pair(pair),h_right(0),h_left(0),balance_factor(0) {
    this->UpdateBalanceFactor();


}


#endif //DATA_STRUCTURES_234218_NODE_H
