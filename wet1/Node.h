//
// Created by Daniel on 4/20/2022.
//

#include "Pair.h"

#ifndef DATA_STRUCTURES_234218_NODE_H

template<class T>
class Node {
public:
    int h_left;
    int h_right;
    int balance_factor;
    Pair<T> pair;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> father;

    int UpdateBalanceFactor() {
        h_left = this->h_left + 1;
        h_right = this->h_right + 1;
        balance_factor = h_left - h_right;
    }
};

#define DATA_STRUCTURES_234218_NODE_H

#endif //DATA_STRUCTURES_234218_NODE_H
