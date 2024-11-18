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

// ��������������� ����������� ������� ��� ������ ������������� �����
// t - ������� ����, ������� ��������������
// pmax - ��������� �� �������� ������������� �����
// max_elem - ������� ������������ �������� �����
// parent - �������� �������� ����
void BinTree::findMaxLeafRecursive(Node* t, Node*& pmax, int& max_elem, Node* parent) {
    if (!t) return; // ���� ���� ������, ������� �� �������

    // ��������, �������� �� ������� ���� ������ (�� ����� ��������)
    if (!t->left && !t->right) {
        // ���� ���� ������ � ��� �������� ������ �������� ���������, ��������� max_elem � pmax
        if (!pmax || t->data > max_elem) {
            max_elem = t->data; // ��������� �������� ������������� �����
            pmax = parent;      // ��������� �������� ����� �����
        }
    }

    // ���������� ������������ ����� � ������ ����������
    findMaxLeafRecursive(t->left, pmax, max_elem, t);
    findMaxLeafRecursive(t->right, pmax, max_elem, t);
}

// �������� ������� ��� �������� ������������� ����� ����������� �������
void BinTree::deleteMaxLeafRecursively() {
    Node* pmax = nullptr;         // ��������� �� �������� ������������� �����
    int max_elem = root->data;    // ��������� �������� ��� ������ ������������� ��������

    // ����� ��������������� ������� ��� ������ ������������� �����
    findMaxLeafRecursive(root, pmax, max_elem);

    // �������� ������������� �����
    if (pmax) { // ���� ������ �������� ������������� �����
        // ���������, �������� �� ������������ ���� ����� ��� ������ �������� ��������
        if (pmax->left && pmax->left->data == max_elem) {
            delete pmax->left; // ������� ����� �������
            pmax->left = nullptr;
        }
        else if (pmax->right && pmax->right->data == max_elem) {
            delete pmax->right; // ������� ������ �������
            pmax->right = nullptr;
        }
    }
}

// ����������� ������� ��� ������ � �������� ������������� �����
// ���������� ��������� �� �������� ���������� ������������� �����
Node* BinTree::deleteMaxLeafIteratively() {
    if (!root) return nullptr; // ���� ������ ������, ���������� nullptr

    Node* pmax = nullptr;       // ��������� �� �������� ������������� �����
    Node* parent = nullptr;     // ������� �������� ��� ������ ������
    int max_elem = root->data;  // ��������� �������� ��� ������ ������������� ��������

    std::stack<Node*> s;        // ���� ��� ������ ������
    Node* t = root;             // �������� ����� � �����

    // ����������� ����� ������
    while (t) {
        // ���� ������� ���� �������� ������
        if (!t->left && !t->right) {
            // ���������, �������� �� �� ������������ ��������� ������
            if (!pmax || t->data > max_elem) {
                max_elem = t->data; // ��������� �������� ������������� �����
                pmax = parent;      // ��������� �������� ������������� �����
            }
        }

        // ������� � ������ �������, �������� ������ � ����, ���� �� ����
        if (t->left) {
            if (t->right) {
                s.push(t->right); // ��������� ������ ���� ��� ����������� ������
            }
            parent = t;
            t = t->left;
        }
        else {
            // ���� ������ ������� ���, �� ���� ������
            if (t->right) {
                parent = t;
                t = t->right;
            }
            else {
                // ���� ��� �� ������, �� ������� ��������, ����� ���� �� �����
                if (!s.empty()) {
                    t = s.top();
                    s.pop();
                }
                else {
                    t = nullptr; // ����������� �����, ���� ���� ����
                }
            }
        }
    }
    // �������� ������������� �����, ���� ������ �������� pmax
    if (pmax) {
        if (pmax->left && pmax->left->data == max_elem) {
            delete pmax->left; // ������� ����� �������, ���� ��� ������������ ����
            pmax->left = nullptr;
        }
        else if (pmax->right && pmax->right->data == max_elem) {
            delete pmax->right; // ������� ������ �������, ���� ��� ������������ ����
            pmax->right = nullptr;
        }
    }

    return pmax; // ���������� ��������� �� �������� ������������� �����
}
