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
    return node->pair.key == key;
};

class MapError : public std::exception {
};

class KeyAlreadyExists : public MapError {
};

class KeyDoesntExist : public MapError {
};


template<class T, class Key>
class Map {
private:
    shared_ptr<Node<T, Key>> head;
    int amount;

    shared_ptr<Node<T, Key>> GetNode(shared_ptr<Node<T, Key>> node, Key key) {
        if (CompareKeys(node, key))
            return node;
        if (key < node->pair.key)
            return GetNode(node->left, key);
        if (key > node->pair.key)
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
        if (key < node->pair.key) {
            if (node->left == NULL)
                return node;
            return GetNodeFather(node->left, key);
        }
        if (key > node->pair.key) {
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


    Pair<T, Key> *ArrayFromTree() {
        auto *array = new Pair<T, Key>[this->amount];
        int i = 0;
        StoreInorder(this->head, array, &i, this->amount);
        return array;
    }

    std::shared_ptr<Node<T, Key>>
    TreeFromArray(std::shared_ptr<Node<T, Key>> father, Pair<T, Key> *array, int first_index, int last_index) {
        if (first_index > last_index)
            return NULL;
        int mid_index = (first_index + last_index) / 2;
        std::shared_ptr<Node<T, Key>> node = std::shared_ptr<Node<T, Key>>(
                new Node<T, Key>(NULL, NULL, father, array[mid_index]));
        node->left = TreeFromArray(node, array, first_index, mid_index - 1);
        node->right = TreeFromArray(node, array, mid_index + 1, last_index);
        node->UpdateBalanceFactor();
        return node;

    }

    Pair<T, Key> *MergeSortedArrays(Pair<T, Key> array1[], Pair<T, Key> array2[], int array1_size, int array2_size) {
        auto *merged = new Pair<T, Key>[array1_size + array2_size];
        int i = 0, j = 0, new_index = 0;
        while (i < array1_size || j < array2_size) {
            if (i == array1_size || array1[i].key >= array2[j].key) {
                merged[new_index] = array2[i];
                new_index++;
                i++;
                continue;
            } else {
                merged[new_index] = array1[j];
                new_index++;
                j++;
                continue;
            }

        }
        return merged;
    }


    void StoreInorder(shared_ptr<Node<T, Key>> node, Pair<T, Key> arr[], int *index, int max, Key max_key = NULL) {
        if (node == NULL)
            return;
        if (*index == max)
            return;
        StoreInorder(node->left, arr, index, max);
        if (max_key != NULL && node->pair.key > max_key)
            return;
        arr[*index] = node->pair;
        (*index)++;
        StoreInorder(node->right, arr, index, max);

    }

    int CountInorder(shared_ptr<Node<T, Key>> node, Key max_key = NULL) {
        if (node == NULL)
            return 0;
        int sum = CountInorder(node->left);
        if (max_key != NULL && node->pair.key > max_key)
            return sum;
        sum++;
        sum += CountInorder(node->right);
        return sum;
    }


public:
    Map();

    Map(Map, Map);

    T &find(Key key);

    void insert(Key key, T element);

    void remove(Key key);

    std::shared_ptr<Node<T, Key>> GetMaxId();

    Pair<T, Key> *GetFirstNum(int NumToReturn);

    Pair<T, Key> *GetObjectsFromKey(Key min_key, Key max_key, int *size);


};

template<class T, class Key>
T &Map<T, Key>::find(Key key) {
    shared_ptr<Node<T, Key>> temp = head;
    shared_ptr<Node<T, Key>> result = GetNode(head, key);
    if (result == NULL)
        throw KeyDoesntExist();
    return result->pair.element;


}


template<class T, class Key>
Map<T, Key>::Map() {
    head = NULL;
    amount = 0;
}

template<class T, class Key>
void Map<T, Key>::insert(Key key, T element) {
    shared_ptr<Node<T, Key>> father = GetNodeFather(head, key);
    if (father->left->pair.key == key || father->right->pair.key == key)
        throw KeyAlreadyExists();
    Pair<T, Key> pair(element, key);
    amount++;
    if (father == NULL) {
        head = std::shared_ptr<Node<T, Key>>(new Node<T, Key>(NULL, NULL, NULL, pair));
        return;
    }
    if (father->pair.key > key) {
        if (father->left == NULL) {
            father->left = std::shared_ptr<Node<T, Key>>(new Node<T, Key>(NULL, NULL, father, pair));
        } else {
            father->left->pair.element = element;
        }
        BalanceRoute(father->left);
    } else {
        if (father->right == NULL) {
            father->right = std::shared_ptr<Node<T, Key>>(new Node<T, Key>(NULL, NULL, father, pair));
        } else {
            father->right->pair.element = element;
        }
        BalanceRoute(father->right);
    }

}

template<class T, class Key>
void Map<T, Key>::remove(Key key) {
    shared_ptr<Node<T, Key>> node = GetNode(head, key);
    if (node == NULL)
        throw KeyDoesntExist();
    std::shared_ptr<Node<T, Key>> temp = NULL;
    amount--;
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
shared_ptr<Node<T, Key>> Map<T, Key>::GetMaxId()
{
    if (head == NULL)
    {
        return NULL;
    }
    return GetRightestNode(head);
}

template<class T, class Key>
Map<T, Key>::Map(Map map1, Map map2) {
    Pair<T, Key> *array1 = map1.ArrayFromTree();
    Pair<T, Key> *array2 = map2.ArrayFromTree();
    Pair<T, Key> *merged = MergeSortedArrays(array1, array2, map1.amount, map2.amount);
    amount = map1.amount + map2.amount;
    head = TreeFromArray(NULL, merged, 0, amount - 1);

}


template<class T, class Key>
Pair<T, Key> *Map<T, Key>::GetFirstNum(int NumToReturn) {
    auto *array = new Pair<T, Key>[NumToReturn];
    int i = 0;
    StoreInorder(this->head, array, &i, NumToReturn);
    return array;
}

template<class T, class Key>
Pair<T, Key> *Map<T, Key>::GetObjectsFromKey(Key min_key, Key max_key, int *size) {
    std::shared_ptr<Node<T, Key>> node = find(min_key);
    std::shared_ptr<Node<T, Key>> father = node;
    while (IsLeftSon(father, father->father)) {
        father = father->father;
    }
    *size = CountInorder(father, max_key);
    auto *array = new Pair<T, Key>[*size];
    int i = 0;
    StoreInorder(father, array, &i, INT16_MAX, max_key);
    return array;
}


#endif //DATA_STRUCTURES_234218_Map_H
