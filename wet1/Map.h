//
// Created by Daniel on 4/20/2022.
//

#include <memory>
#include "Node.h"
#include "Pair.h"

using std::shared_ptr;

#ifndef DATA_STRUCTURES_234218_Map_H


bool CompareKeys(shared_ptr<Node<int>> &node, int key) {
    return node->pair.key == key;
};

class NodeNotFound : public std::exception {
};

class NodeHasNoFather : public std::exception {
};

template<class T>
class Map {
private:
    shared_ptr<Node<int>> head;

    shared_ptr<Node<int>> &GetNode(shared_ptr<Node<int>> node, int key) {
        if (CompareKeys(node, key))
            return node;
        if (key < node->pair.key)
            return GetNode(node->left);
        if (key > node->pair.key)
            return GetNode(node->right);
        throw NodeNotFound();
    }

    shared_ptr<Node<int>> &GetNodeFather(shared_ptr<Node<int>> node, int key) {
        if (CompareKeys(node->left, key))
            return node;
        if (CompareKeys(node->right, key))
            return node;
        if (key < node->pair.key)
            return GetNodeFather(node->left);
        if (key > node->pair.key)
            return GetNodeFather(node->right);
        throw NodeHasNoFather();
    }

    void BalanceRoute(shared_ptr<Node<int>> head, shared_ptr<Node<int>> updated_node) {
        while (updated_node->father != nullptr) {
            updated_node->UpdateBalanceFactor();
            if (updated_node->balance_factor > -1 && updated_node->balance_factor < 1) {
                if (updated_node->balance_factor == 2 && updated_node->left->balance_factor >= 0)
                    LL_Roll(updated_node);
                if (updated_node->balance_factor == 2 && updated_node->left->balance_factor == -1)
                    LR_Roll(updated_node);
                if (updated_node->balance_factor == -2 && updated_node->right->balance_factor == 1)
                    RL_Roll(updated_node);
                if (updated_node->balance_factor == -2 && updated_node->right->balance_factor <= 0)
                    RR_Roll(updated_node);
                break;
            }

        }
    }

    bool IsLeftSon(shared_ptr<Node<int>> son, shared_ptr<Node<int>> father) {
        return father->left == son;
    }

    void LL_Roll(shared_ptr<Node<int>> node) {
        shared_ptr<Node<int>> temp = node->left;
        shared_ptr<Node<int>> father = node->father;
        node->left = temp->right;
        temp->right = node;
        if (IsLeftSon(node, father)) {
            father->left = temp;
        } else {
            father->right = temp;
        }
        node->UpdateBalanceFactor();
        temp->UpdateBalanceFactor();
        father->UpdateBalanceFactor();


    }

    void RR_Roll(shared_ptr<Node<int>> node) {
        shared_ptr<Node<int>> temp = node->right;
        shared_ptr<Node<int>> father = node->father;
        node->right = temp->left;
        temp->left = node;
        if (IsLeftSon(node, father)) {
            father->left = temp;
        } else {
            father->right = temp;
        }
        node->UpdateBalanceFactor();
        temp->UpdateBalanceFactor();
        father->UpdateBalanceFactor();

    }

    void RL_Roll(shared_ptr<Node<int>> node) {
        LL_Roll(node->right);
        RR_Roll(node);


    }

    void LR_Roll(shared_ptr<Node<int>> node) {
        RR_Roll(node->left);
        LL_Roll(node);

    }


public:
    Map();

    T &find(int x);

    void insert(int x);

};

template<class T>
T &Map<T>::find(int x) {
    shared_ptr<Node<int>> temp = head;
    return (GetNode(head, x))->pair.element;


}


template<class T>
Map<T>::Map() {
    head = nullptr;
}

template<class T>
void Map<T>::insert(int x) {

}


#define DATA_STRUCTURES_234218_Map_H

#endif //DATA_STRUCTURES_234218_Map_H
