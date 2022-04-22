//
// Created by Daniel on 4/20/2022.
//

#include <memory>
#include "Node.h"

using std::shared_ptr;

#ifndef DATA_STRUCTURES_234218_Map_H
#define DATA_STRUCTURES_234218_Map_H

template<class T, class Key>
bool CompareKeys(shared_ptr<Node<T, Key>> node, Key key) {
    if (node == NULL)
        return false;
    return node->key == key;
};


template<class T, class Key>
class Map {
private:
    shared_ptr<Node<T, Key>> head;

    shared_ptr<Node<T, Key>> GetNode(shared_ptr<Node<T, Key>> node, Key key) {
        if (CompareKeys(node, key))
            return node;
        if (key < node->key)
            return GetNode(node->left, key);
        if (key > node->key)
            return GetNode(node->right, key);
        return NULL;
    }

    std::shared_ptr<Node<T, Key>> GetLeftestNode(std::shared_ptr<Node<T, Key>> node) {
        if (node->left == NULL)
            return node;
        return GetLeftestNode(node->left);
    }

    std::shared_ptr<Node<T, Key>> GetRightestNode(std::shared_ptr<Node<T, Key>> node) {
        if (node->right == NULL)
            return node;
        return GetRightestNode(node->right);
    }

    shared_ptr<Node<T, Key>> GetNodeFather(shared_ptr<Node<T, Key>> node, Key key) {
        if (node == NULL) {
            return NULL;
        }
        if (CompareKeys(node->left, key))
            return node;
        if (CompareKeys(node->right, key))
            return node;
        if (key < node->key) {
            if (node->left == NULL)
                return node;
            return GetNodeFather(node->left, key);
        }
        if (key > node->key) {
            if (node->right == NULL)
                return node;
            return GetNodeFather(node->right, key);
        }
        return NULL;
    }

    void BalanceRoute(shared_ptr<Node<T, Key>> updated_node) {
        while (updated_node != NULL) {
            updated_node->UpdateBalanceFactor();
            if (updated_node->balance_factor < -1 || updated_node->balance_factor > 1) {
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
            updated_node = updated_node->father;
        }
    }

    bool IsLeftSon(shared_ptr<Node<T, Key>> son, shared_ptr<Node<T, Key>> father) {
        return father->left == son;
    }

    void LL_Roll(shared_ptr<Node<T, Key>> node) {
        shared_ptr<Node<T, Key>> temp = node->left;
        shared_ptr<Node<T, Key>> father = node->father;
        node->left = temp->right;
        temp->right = node;
        if (father == NULL)
            head = temp;
        else {
            if (IsLeftSon(node, father)) {
                father->left = temp;
            } else {
                father->right = temp;
            }
            father->UpdateBalanceFactor();
        }
        node->UpdateBalanceFactor();
        temp->UpdateBalanceFactor();
    }

    void RR_Roll(shared_ptr<Node<T, Key>> node) {
        shared_ptr<Node<T, Key>> temp = node->right;
        shared_ptr<Node<T, Key>> father = node->father;
        node->right = temp->left;
        temp->left = node;
        if (father == NULL) {
            head = temp;
        } else {
            if (IsLeftSon(node, father)) {
                father->left = temp;
            } else {
                father->right = temp;
            }
            father->UpdateBalanceFactor();
        }

        node->UpdateBalanceFactor();
        temp->UpdateBalanceFactor();

    }

    void RL_Roll(shared_ptr<Node<T, Key>> node) {
        LL_Roll(node->right);
        RR_Roll(node);


    }

    void LR_Roll(shared_ptr<Node<T, Key>> node) {
        RR_Roll(node->left);
        LL_Roll(node);

    }


public:
    Map();

    T &find(Key key);

    void insert(Key key, T element);

    void remove(Key key);

    std::shared_ptr<Node<T, Key>> GetMaxId();

};

template<class T, class Key>
T &Map<T, Key>::find(Key x) {
    shared_ptr<Node<T, Key>> temp = head;
    return (GetNode(head, x))->element;


}


template<class T, class Key>
Map<T, Key>::Map() {
    head = NULL;
}

template<class T, class Key>
void Map<T, Key>::insert(Key key, T element) {
    shared_ptr<Node<T, Key>> father = GetNodeFather(head, key);
    if (father == NULL) {
        head = std::shared_ptr<Node<T, Key>>(new Node<T, Key>(NULL, NULL, NULL, key, element));
        return;
    }
    if (father->key > key) {
        if (father->left == NULL) {
            father->left = std::shared_ptr<Node<T, Key>>(new Node<T, Key>(NULL, NULL, father, key, element));
        } else {
            father->left->element = element;
        }
        BalanceRoute(father->left);
    } else {
        if (father->right == NULL) {
            father->right = std::shared_ptr<Node<T, Key>>(new Node<T, Key>(NULL, NULL, father, key, element));
        } else {
            father->right->element = element;
        }
        BalanceRoute(father->right);
    }

}

template<class T, class Key>
void Map<T, Key>::remove(Key key) {
    shared_ptr<Node<T, Key>> node = GetNode(head, key);
    std::shared_ptr<Node<T, Key>> temp = NULL;
    if (node->right != NULL && node->left != NULL) {
        if (node->father == NULL) {
            head = node->right;
            head->father = NULL;
            temp = node->left;
            std::shared_ptr<Node<T, Key>> leftest = GetLeftestNode(node->right);
            leftest->left = node->left;
            node->left->father = leftest;
        } else {
            if (IsLeftSon(node, node->father)) {
                temp = node->left;
                std::shared_ptr<Node<T, Key>> leftest = GetLeftestNode(node->right);
                leftest->left = temp;
                temp->father = leftest;
                node->father->left = node->right;
                node->right->father = node->father;
            } else {
                temp = node->right;
                std::shared_ptr<Node<T, Key>> rightest = GetRightestNode(node->left);
                rightest->right = temp;
                temp->father = rightest;
                node->father->right = node->left;
                node->left->father = node->father;


            }
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

template<class T, class Key>
shared_ptr<Node<T, Key>> Map<T, Key>::GetMaxId() {
    return GetRightestNode();
}


#endif //DATA_STRUCTURES_234218_Map_H
