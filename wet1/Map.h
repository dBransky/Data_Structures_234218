//
// Created by Daniel on 4/20/2022.
//

#include <memory>
#include "Node.h"


#ifndef DATA_STRUCTURES_234218_Map_H
#define DATA_STRUCTURES_234218_Map_H

template<class T, class Key>
bool CompareKeys(Node<T, Key> *node, Key key) {
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
    Node<T, Key> *head;
    int amount;

    Node<T, Key> *GetNode(Node<T, Key> *node, Key key) {
        if (node == NULL)
            return NULL;
        if (CompareKeys(node, key))
            return node;
        if (key < node->pair.key)
            return GetNode(node->left, key);
        if (key > node->pair.key)
            return GetNode(node->right, key);
        return NULL;
    }

    Node<T, Key> *GetLeftestNode(Node<T, Key> *node) {
        if (node->left == NULL)
            return node;
        return GetLeftestNode(node->left);
    }

    Node<T, Key> *GetRightestNode(Node<T, Key> *node) {
        if (node->right == NULL)
            return node;
        return GetRightestNode(node->right);
    }

    Node<T, Key> *GetNodeFather(Node<T, Key> *node, Key key) {
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

    void BalanceRoute(Node<T, Key> *updated_node) {
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

    bool IsLeftSon(Node<T, Key> *son, Node<T, Key> *father) {
        if (father == NULL || son == NULL)
            return false;
        return father->left == son;
    }

    void LL_Roll(Node<T, Key> *node) {
        Node<T, Key> *temp = node->left;
        Node<T, Key> *father = node->father;
        node->left = temp->right;
        if (node->left != NULL)
            temp->right->father = node->left;
        temp->right = node;
        node->father = temp;
        if (father == NULL) {
            head = temp;
            head->father = NULL;
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

    void RR_Roll(Node<T, Key> *node) {
        Node<T, Key> *temp = node->right;
        Node<T, Key> *father = node->father;
        node->right = temp->left;
        if (node->right != NULL)
            temp->left->father = node->right;
        temp->left = node;
        node->father = temp;
        if (father == NULL) {
            head = temp;
            head->father = NULL;
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

    void RL_Roll(Node<T, Key> *node) {
        LL_Roll(node->right);
        RR_Roll(node);


    }

    void LR_Roll(Node<T, Key> *node) {
        RR_Roll(node->left);
        LL_Roll(node);

    }


    Pair<T, Key> *ArrayFromTree() {
        auto *array = new Pair<T, Key>[this->amount];
        int i = 0;
        StoreInorder(this->head, array, &i, this->amount);
        return array;
    }

    Node<T, Key> *
    TreeFromArray(Node<T, Key> *father, Pair<T, Key> *array, int first_index, int last_index) {
        if (first_index > last_index)
            return NULL;
        int mid_index = (first_index + last_index) / 2;
        auto *node =
                new Node<T, Key>(NULL, NULL, father, array[mid_index]);
        node->left = TreeFromArray(node, array, first_index, mid_index - 1);
        node->right = TreeFromArray(node, array, mid_index + 1, last_index);
        node->UpdateBalanceFactor();
        return node;

    }

    Pair<T, Key> *MergeSortedArrays(Pair<T, Key> array1[], Pair<T, Key> array2[], int array1_size, int array2_size) {
        auto *merged = new Pair<T, Key>[array1_size + array2_size];
        int i = 0, j = 0, new_index = 0;
        while (i < array1_size || j < array2_size) {
            if (j == array2_size || array1[i].key >= array2[j].key) {
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

    void StoreInorder(Node<T, Key> *node, Pair<T, Key> arr[], int *index, int max, Key *max_key = NULL) {
        if (node == NULL)
            return;
        if (*index == max)
            return;
        StoreInorder(node->left, arr, index, max, max_key);
        if (max_key != NULL) {
            if (node->pair.key > *max_key)
                return;
        }
        arr[*index] = node->pair;
        (*index)++;
        StoreInorder(node->right, arr, index, max, max_key);

    }

    void FreePostOrder(Node<T, Key> *node) {
        if (node == NULL)
            return;
        FreePostOrder(node->left);
        FreePostOrder(node->right);
        delete (node);
    }

    void NULLInorder(Node<T, Key> *node) {
        if (node == NULL)
            return;
        NULLInorder(node->left);
        NULLInorder(node->right);
        node->pair.element = NULL;
    }

    int CountInorder(Node<T, Key> *node, Key *max_key = NULL) {
        if (node == NULL)
            return 0;
        int sum = CountInorder(node->left);
        if (max_key != NULL) {
            if (node->pair.key > *max_key)
                return sum;
        }
        sum++;
        sum += CountInorder(node->right);
        return sum;
    }


public:
    Map();

    ~Map();

    T &find(Key key);

    void insert(Key key, T element);

    void remove(Key key);

    void merge(Map &);

    T GetMaxId();

    Pair<T, Key> *GetFirstNum(int NumToReturn);

    Pair<T, Key> *GetObjectsFromKey(Key min_key, Key max_key, int *size);


};

template<class T, class Key>
T &Map<T, Key>::find(Key key) {
    Node<T, Key> *result = GetNode(head, key);
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
    Node<T, Key> *father = GetNodeFather(head, key);
    if (father != NULL) {
        if ((father->left != NULL && father->left->pair.key == key) ||
            (father->right != NULL && father->right->pair.key == key))
            throw KeyAlreadyExists();
    }
    Pair<T, Key> pair(element, key);
    amount++;
    if (father == NULL) {
        head = new Node<T, Key>(NULL, NULL, NULL, pair);
        return;
    }
    if (father->pair.key > key) {
        if (father->left == NULL) {
            father->left = new Node<T, Key>(NULL, NULL, father, pair);
        } else {
            father->left->pair.element = element;
        }
        BalanceRoute(father->left);
    } else {
        if (father->right == NULL) {
            father->right = new Node<T, Key>(NULL, NULL, father, pair);
        } else {
            father->right->pair.element = element;
        }
        BalanceRoute(father->right);
    }
}

template<class T, class Key>
void Map<T, Key>::remove(Key key) {
    Node<T, Key> *node = GetNode(head, key);
    if (node == NULL)
        throw KeyDoesntExist();
    Node<T, Key> *temp = NULL;
    amount--;
    if (node->right != NULL && node->left != NULL) {
        if (node->father == NULL) {
            head = node->right;
            head->father = NULL;
            temp = node->left;
            Node<T, Key> *leftest = GetLeftestNode(node->right);
            leftest->left = node->left;
            node->left->father = leftest;
        } else {
            if (IsLeftSon(node, node->father)) {
                temp = node->left;
                Node<T, Key> *leftest = GetLeftestNode(node->right);
                leftest->left = temp;
                temp->father = leftest;
                node->father->left = node->right;
                node->right->father = node->father;
            } else {
                temp = node->right;
                Node<T, Key> *rightest = GetRightestNode(node->left);
                rightest->right = temp;
                temp->father = rightest;
                node->father->right = node->left;
                node->left->father = node->father;


            }
        }
        BalanceRoute(temp);
        return;
    }
    if (node->right == NULL && node->left == NULL) {
        temp = node->father;
        if (node->father == NULL) {
            head = temp;
        } else {
            if (IsLeftSon(node, node->father))
                node->father->left = NULL;
            else
                node->father->right = NULL;
        }
    } else {
        if (node->right == NULL)
            temp = node->left;
        if (node->left == NULL)
            temp = node->right;
        if (node->father == NULL) {
            head = temp;
            temp->father = NULL;
        } else {
            if (IsLeftSon(node, node->father)) {
                {
                    node->father->left = temp;
                    temp->father = node->father;
                }
            } else {
                node->father->right = temp;
                temp->father = node->father;
            }
        }
    }
    delete (node);
    BalanceRoute(temp);
}

template<class T, class Key>
T Map<T, Key>::GetMaxId() {
    if (head == NULL) {
        return NULL;
    }
    return GetRightestNode(head)->pair.element;
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
    Node<T, Key> *father = GetNodeFather(head, min_key);
    if (father->pair.key < min_key) {
        *size = 0;
        return NULL;
    }
    while (IsLeftSon(father, father->father)) {
        father = father->father;
    }
    *size = CountInorder(father, &max_key);
    auto *array = new Pair<T, Key>[*size];
    int i = 0;
    StoreInorder(father, array, &i, INT16_MAX, &max_key);
    return array;
}

template<class T, class Key>
Map<T, Key>::~Map() {
    FreePostOrder(head);
}

template<class T, class Key>
void Map<T, Key>::merge(Map &map) {
    Pair<T, Key> *array1 = map.ArrayFromTree();
    Pair<T, Key> *array2 = this->ArrayFromTree();
    Pair<T, Key> *merged = MergeSortedArrays(array1, array2, map.amount, this->amount);
    for (int i = 0; i < map.amount; ++i) {
        array1[i].element = NULL;
    }
    for (int i = 0; i < this->amount; ++i) {
        array2[i].element = NULL;
    }
    NULLInorder(map.head);
    NULLInorder(this->head);
    delete[] array1;
    delete[] array2;
    amount = map.amount + this->amount;
    head = TreeFromArray(NULL, merged, 0, amount - 1);
    delete[] merged;

}


#endif //DATA_STRUCTURES_234218_Map_H
