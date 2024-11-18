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

    // ������� ��� ������ � �������� ������������� �����
    void deleteMaxLeafRecursively();
    Node* deleteMaxLeafIteratively();  // ���������: ������� pmax �� ����������

private:
    // ��������������� ������� ��� ������������ ������
    void findMaxLeafRecursive(Node* t, Node*& pmax, int& max_elem, Node* parent = nullptr);
};