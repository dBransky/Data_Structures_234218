//
// Created by Daniel on 4/20/2022.
//


#ifndef DATA_STRUCTURES_234218_NODE_H
#define DATA_STRUCTURES_234218_NODE_H

template<class T>
class Node {
public:
    int h_left;
    int h_right;
    int balance_factor;
    int key;
    T element;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> father;

    Node(std::shared_ptr<Node<T>> left, std::shared_ptr<Node<T>> right, std::shared_ptr<Node<T>> father, int key,
         T element);

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

template<class T>
Node<T>::Node(std::shared_ptr<Node<T>> left, std::shared_ptr<Node<T>> right, std::shared_ptr<Node<T>> father, int key,
              T element):left(left), right(right), father(father), key(key), element(element) {
    this->UpdateBalanceFactor();


}


#endif //DATA_STRUCTURES_234218_NODE_H
