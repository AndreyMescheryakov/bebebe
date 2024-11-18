#pragma once
#include <stack>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int data);
    ~Node();

    void add(int data);
    void print(int level);
    void clear();
};

struct BinTree {
    Node* root;

    BinTree();
    ~BinTree();
    void add(int data);
    void print();
    void clear();

    // Функции для поиска и удаления максимального листа
    void deleteMaxLeafRecursively();
    Node* deleteMaxLeafIteratively();  // Изменение: удалили pmax из параметров

private:
    // Вспомогательная функция для рекурсивного поиска
    void findMaxLeafRecursive(Node* t, Node*& pmax, int& max_elem, Node* parent = nullptr);
};