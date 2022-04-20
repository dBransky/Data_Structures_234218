//
// Created by Daniel on 4/20/2022.
//

#include <memory>
#include "Node.h"

using std::shared_ptr;

#ifndef DATA_STRUCTURES_234218_Map_H

template<class T>
bool CompareKeys(shared_ptr<Node<T>> &node, int key) {
    return node->key == key;
};

class NodeNotFound : public std::exception {
};

class NodeHasNoFather : public std::exception {
};

template<class T>
class Map {
private:
    shared_ptr<Node<T>> head;

    shared_ptr<Node<T>> &GetNode(shared_ptr<Node<T>> node, int key) {
        if (CompareKeys(node, key))
            return node;
        if (key < node->key)
            return GetNode(node->left);
        if (key > node->key)
            return GetNode(node->right);
        throw NodeNotFound();
    }

    std::shared_ptr<Node<T>> &GetLeftestNode(std::shared_ptr<Node<T>> node) {
        if (node->left == NULL)
            return node;
        return GetLeftestNode(node->left);
    }

    shared_ptr<Node<T>> &GetNodeFather(shared_ptr<Node<T>> node, int key) {
        if (CompareKeys(node->left, key))
            return node;
        if (CompareKeys(node->right, key))
            return node;
        if (key < node->key) {
            if (node->left == NULL)
                return node;
            return GetNodeFather(node->left);
        }
        if (key > node->key) {
            if (node->right == NULL)
                return node;
            return GetNodeFather(node->right);
        }
        throw NodeHasNoFather();
    }

    void BalanceRoute(shared_ptr<Node<T>> head, shared_ptr<Node<T>> updated_node) {
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

    bool IsLeftSon(shared_ptr<Node<T>> son, shared_ptr<Node<T>> father) {
        return father->left == son;
    }

    void LL_Roll(shared_ptr<Node<T>> node) {
        shared_ptr<Node<T>> temp = node->left;
        shared_ptr<Node<T>> father = node->father;
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

    void RR_Roll(shared_ptr<Node<T>> node) {
        shared_ptr<Node<T>> temp = node->right;
        shared_ptr<Node<T>> father = node->father;
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

    void RL_Roll(shared_ptr<Node<T>> node) {
        LL_Roll(node->right);
        RR_Roll(node);


    }

    void LR_Roll(shared_ptr<Node<T>> node) {
        RR_Roll(node->left);
        LL_Roll(node);

    }


public:
    Map();

    T &find(int key);

    void insert(int key, T element);

    void remove(int key);

};

template<class T>
T &Map<T>::find(int x) {
    shared_ptr<Node<T>> temp = head;
    return (GetNode(head, x))->element;


}


template<class T>
Map<T>::Map() {
    head = nullptr;
}

template<class T>
void Map<T>::insert(int key, T element) {
    shared_ptr<Node<T>> father = GetNodeFather(head, key);
    if (father->key > key) {
        if (father->left == NULL) {
            father->left = new Node<T>(NULL, NULL, father, key, element);
        } else {
            father->left->element = element;
        }
        BalanceRoute(father->left);
    } else {
        if (father->right == NULL) {
            father->right = new Node<T>(NULL, NULL, father, key, element);
        } else {
            father->right->element = element;
        }
        BalanceRoute(father->right);
    }

}

template<class T>
void Map<T>::remove(int key) {
    shared_ptr<Node<T>> node = GetNode(head, key);
    std::shared_ptr<Node<T>> temp = NULL;
    if (node->right != NULL && node->left != NULL) {
        if (IsLeftSon(node, node->father)) {
            temp = node->left;
            GetLeftestNode(node->right)->left = temp;
            node->father->left = node->right;
        } else {
            temp = node->right;
            GetLeftestNode(node->left)->right = temp;
            node->father->right = node->left;

        }
        BalanceRoute(temp);
        return;
    }
    if (node->right == NULL)
        temp = node->left;
    if (node->left == NULL)
        temp = node->right;
    if (IsLeftSon(node, node->father)) {
        node->father->left = temp;
    } else
        node->father->right = temp;
    BalanceRoute(temp);
}


#define DATA_STRUCTURES_234218_Map_H

#endif //DATA_STRUCTURES_234218_Map_H
