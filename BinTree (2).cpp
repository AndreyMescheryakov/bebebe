#include "BinTree.h"
#include <iostream>
#include <stack>

Node::Node(int data) {
    this->data = data;
    left = nullptr;
    right = nullptr;
}

Node::~Node() {
    clear();
}

void Node::add(int data) {
    if (data == this->data) {
        return;
    }
    if (data < this->data) {
        if (left == nullptr)
            left = new Node(data);
        else
            left->add(data);
    }
    else {
        if (right == nullptr)
            right = new Node(data);
        else
            right->add(data);
    }
}

void Node::print(int level) {
    if (left) {
        left->print(level + 1);
    }
    for (int i = 0; i < level; ++i)
        std::cout << "   ";
    std::cout << data << std::endl;
    if (right) {
        right->print(level + 1);
    }
}

void Node::clear() {
    if (left) {
        delete left;
        left = nullptr;
    }
    if (right) {
        delete right;
        right = nullptr;
    }
}

BinTree::BinTree() {
    root = nullptr;
}

BinTree::~BinTree() {
    clear();
}

void BinTree::add(int data) {
    if (!root) {
        root = new Node(data);
    }
    else {
        root->add(data);
    }
}

void BinTree::print() {
    if (!root) std::cout << "Derevo empty\n";
    else root->print(0);
}

void BinTree::clear() {
    if (root) {
        root->clear();
        root = nullptr;
    }
}

// Вспомогательная рекурсивная функция для поиска максимального листа
// t - текущий узел, который обрабатывается
// pmax - указатель на родителя максимального листа
// max_elem - текущее максимальное значение листа
// parent - родитель текущего узла
void BinTree::findMaxLeafRecursive(Node* t, Node*& pmax, int& max_elem, Node* parent) {
    if (!t) return; // Если узел пустой, выходим из функции

    // Проверка, является ли текущий узел листом (не имеет потомков)
    if (!t->left && !t->right) {
        // Если лист найден и его значение больше текущего максимума, обновляем max_elem и pmax
        if (!pmax || t->data > max_elem) {
            max_elem = t->data; // Обновляем значение максимального листа
            pmax = parent;      // Сохраняем родителя этого листа
        }
    }

    // Рекурсивно обрабатываем левое и правое поддеревья
    findMaxLeafRecursive(t->left, pmax, max_elem, t);
    findMaxLeafRecursive(t->right, pmax, max_elem, t);
}

// Основная функция для удаления максимального листа рекурсивным методом
void BinTree::deleteMaxLeafRecursively() {
    Node* pmax = nullptr;         // Указатель на родителя максимального листа
    int max_elem = root->data;    // Начальное значение для поиска максимального элемента

    // Вызов вспомогательной функции для поиска максимального листа
    findMaxLeafRecursive(root, pmax, max_elem);

    // Удаление максимального листа
    if (pmax) { // Если найден родитель максимального листа
        // Проверяем, является ли максимальный лист левым или правым потомком родителя
        if (pmax->left && pmax->left->data == max_elem) {
            delete pmax->left; // Удаляем левый потомок
            pmax->left = nullptr;
        }
        else if (pmax->right && pmax->right->data == max_elem) {
            delete pmax->right; // Удаляем правый потомок
            pmax->right = nullptr;
        }
    }
}

// Итеративная функция для поиска и удаления максимального листа
// Возвращает указатель на родителя удаленного максимального листа
Node* BinTree::deleteMaxLeafIteratively() {
    if (!root) return nullptr; // Если дерево пустое, возвращаем nullptr

    Node* pmax = nullptr;       // Указатель на родителя максимального листа
    Node* parent = nullptr;     // Текущий родитель для обхода дерева
    int max_elem = root->data;  // Начальное значение для поиска максимального элемента

    std::stack<Node*> s;        // Стек для обхода дерева
    Node* t = root;             // Начинаем обход с корня

    // Итеративный обход дерева
    while (t) {
        // Если текущий узел является листом
        if (!t->left && !t->right) {
            // Проверяем, является ли он максимальным найденным листом
            if (!pmax || t->data > max_elem) {
                max_elem = t->data; // Обновляем значение максимального листа
                pmax = parent;      // Сохраняем родителя максимального листа
            }
        }

        // Переход к левому потомку, добавляя правый в стек, если он есть
        if (t->left) {
            if (t->right) {
                s.push(t->right); // Сохраняем правый узел для дальнейшего обхода
            }
            parent = t;
            t = t->left;
        }
        else {
            // Если левого потомка нет, но есть правый
            if (t->right) {
                parent = t;
                t = t->right;
            }
            else {
                // Если нет ни левого, ни правого потомков, берем узел из стека
                if (!s.empty()) {
                    t = s.top();
                    s.pop();
                }
                else {
                    t = nullptr; // Заканчиваем обход, если стек пуст
                }
            }
        }
    }
    // Удаление максимального листа, если найден родитель pmax
    if (pmax) {
        if (pmax->left && pmax->left->data == max_elem) {
            delete pmax->left; // Удаляем левый потомок, если это максимальный лист
            pmax->left = nullptr;
        }
        else if (pmax->right && pmax->right->data == max_elem) {
            delete pmax->right; // Удаляем правый потомок, если это максимальный лист
            pmax->right = nullptr;
        }
    }

    return pmax; // Возвращаем указатель на родителя максимального листа
}
