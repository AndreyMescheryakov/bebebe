#include <iostream>
#include <fstream>
#include "BinTree.h"

// ������� ��� ���������� ������ �� ������
Node* buildTree(const std::string& data, int& pos) {
    if (pos >= data.size() || data[pos] == '*') {
        ++pos;
        return nullptr;
    }

    Node* node = new Node(data[pos++]);
    node->left = buildTree(data, pos);
    node->right = buildTree(data, pos);

    return node;
}

int main() {
    // ������ ������ �� ����� input.txt
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "������ �������� �����!" << std::endl;
        return 1;
    }

    std::string data;
    infile >> data;
    infile.close();

    int pos = 0;
    BinTree tree;
    tree.root = buildTree(data, pos);

    std::cout << "��������� ������ �� ��������:" << std::endl;
    tree.print();

    // ����� ������� ��������
    int choice;
    std::cout << "�������� ����� �������� ������������� �����:\n";
    std::cout << "1. ����������� �����\n";
    std::cout << "2. ����������� �����\n";
    std::cout << "������� ����� ������ (1 ��� 2): ";
    std::cin >> choice;

    if (choice == 1) {
        // ����� ����������� �������
        tree.deleteMaxLeafRecursively();
        std::cout << "������������ ���� ������ ����������." << std::endl;
    }
    else if (choice == 2) {
        // ����� ����������� ������� � ��������� �������� ���������� ����
        Node* pmax = tree.deleteMaxLeafIteratively();

        if (pmax) {
            std::cout << "�������� ���������� ������������� �����: " << pmax->data << std::endl;
        }
        else {
            std::cout << "������������ ���� � ��� ������ ������, ��� ������ �����." << std::endl;
        }
    }
    else {
        std::cerr << "�������� �����. ����������, ������������� ��������� � ������� 1 ��� 2." << std::endl;
        return 1;
    }

    // ������ ��������� ������ ����� ��������
    std::cout << "��������� ������ ����� �������� ������������� �����:" << std::endl;
    tree.print();

    return 0;
}


//#include <iostream>
//#include <fstream>
//#include <stack>
//
//using TInfo = int;
//
//namespace tree {
//
//	struct NODE
//	{
//		TInfo info;
//		NODE* left{}, * right{};
//		NODE(TInfo info = 0, NODE* left = nullptr, NODE* right = nullptr)
//		{
//			this->info = info;
//			this->left = left;
//			this->right = right;
//		}
//	};
//
//	using Tree = NODE*;
//
//	Tree build(std::ifstream& file, int size)
//	{
//		Tree result{};
//		if (size)
//		{
//			TInfo x{};
//			file >> x;
//			result = new NODE(x);
//			result->left = build(file, size / 2);
//			result->right = build(file, size - size / 2 - 1);
//		}
//		return result;
//	}
//
//	Tree build_from_string(std::istream& in) {
//		char c;
//		in >> c;
//
//		if (c == '*') {
//			return nullptr; // ������ ����
//		}
//
//		Tree node = new NODE(c);
//		node->left = build_from_string(in);
//		node->right = build_from_string(in);
//
//		return node;
//	}
//
//	void clear(Tree& t)
//	{
//		if (t)
//		{
//			clear(t->left);
//			clear(t->right);
//			delete t;
//			t = nullptr;
//		}
//	}
//
//	void print(tree::Tree t, int level, char branch = '-') {
//		if (t) {
//			print(t->right, level + 1, 'R');
//			for (int i = 0; i < level; ++i)
//				std::cout << "    ";
//			std::cout << branch << "-- " << t->info << '\n';
//			print(t->left, level + 1, 'L');
//		}
//	}
//
//	bool is_leaf(Tree& t)
//	{
//		return !t->right && !t->left;
//	}
//}
//
//// ������: ����� �������� � ������� ������������ ������� - ����
//
//void task6_rec(tree::Tree& t, tree::Tree& pmax, TInfo& max_elem) {
//	if (t) {
//		// ���� ����� ����, ��������� ����� �� �������� ��������
//		if (t->left && tree::is_leaf(t->left) && (!pmax || t->left->info > max_elem)) {
//			max_elem = t->left->info;
//			pmax = t;
//		}
//		// ���� ������ ����, ��������� ����� �� �������� ��������
//		if (t->right && tree::is_leaf(t->right) && (!pmax || t->right->info > max_elem)) {
//			max_elem = t->right->info;
//			pmax = t;
//		}
//		// ���������� ������� ������
//		task6_rec(t->left, pmax, max_elem);
//		task6_rec(t->right, pmax, max_elem);
//	}
//}
///*
//void task6_iter(tree::Tree t, tree::Tree& pmax, TInfo& max_elem) {
//	if (!t) return;
//
//	std::stack<tree::Tree> node_stack;   // ���� ��� ������ �����
//	std::stack<tree::Tree> parent_stack; // ���� ��� �������� ��������� �����
//
//	node_stack.push(t);
//	parent_stack.push(nullptr);
//
//	while (!node_stack.empty()) {
//		tree::Tree current = node_stack.top();
//		tree::Tree parent = parent_stack.top();
//		node_stack.pop(); // ������� �� ����� ��� ��� ������ ��������������
//		parent_stack.pop();
//
//		if (tree::is_leaf(current)) {
//			// ���� ������� ���� � ����, ��������� ��������, ���� �����
//			if (!pmax || current->info > max_elem) {
//				max_elem = current->info;
//				pmax = parent;
//			}
//		}
//		else {
//			// ���� � �������� ���� ���� ������ �������, ��������� ��� � ����
//			if (current->right) {
//				node_stack.push(current->right);
//				parent_stack.push(current);
//			}
//			// ���� � �������� ���� ���� ����� �������, ��������� ��� � ����
//			if (current->left) {
//				node_stack.push(current->left);
//				parent_stack.push(current);
//			}
//		}
//	}
//}
//*/
//
////������ ���� ������� Tree � ����� ���������� pmax
//void task6_iter(tree::Tree t, tree::Tree& pmax, TInfo& max_elem) {
//	std::stack<tree::Tree> s; // ���� ��� �������� ������ ��������
//	tree::Tree parent = nullptr;
//
//	while (t) {
//		if (tree::is_leaf(t)) {
//			if (!pmax || t->info > max_elem) {
//				max_elem = t->info;
//				pmax = parent;
//			}
//		}
//
//		if (t->left) {
//			// ���� ���� � ������ �������, ��������� ��� � ����
//			if (t->right) {
//				s.push(t->right);
//			}
//			// ��������� � ������ �������, ��������� ��������
//			parent = t;
//			t = t->left;
//		}
//		// ���� ������ ������� ���, �� ���� ������, ��������� � �������
//		else {
//			if (t->right) {
//				parent = t;
//				t = t->right;
//			}
//			// ���� ��� �� ������, �� ������� �������, ��������� � ���� �� �����
//			else {
//				if (!s.empty()) {
//					t = s.top();
//					s.pop();
//				}
//				else {
//					t = nullptr;
//				}
//			}
//		}
//	}
//}
//
////while (t) {
////	<��������� t->info>
////		if (t->left) {
////			if (t->right) {
////				s.push(t->right)
////			t = t->left
////			}
////		}
////		else {
////			if (t->right)
////				t = t->right
////			else//��� �� ������ �� �������
////				if (!stack.empty())
////					t = s.top(); s.pop();
////				else t = nullptr;
////		}
////}
//
//void delete_max_leaf(tree::Tree& t) {
//	if (!t) return;
//
//	tree::Tree pmax = nullptr; // �������� ������������� �����
//	TInfo max_elem = '\0';     // ������������ ������� ����� �������, ���������� ������ ������
//
//	// ����������� ����� ��� ������ ������������� �����
//	/*
//	task6_rec(t, pmax, max_elem);  // ����������� ����� ������������� �����
//	*/
//
//	// ����������� ����� ��� ������ ������������� ����� 
//	task6_iter(t, pmax, max_elem);  // ����������� ����� ������������� �����
//
//	// �������� � ����� ���������� � ������������ ����� ����� ���������
//	if (pmax) {
//		std::cout << "������������ ���� ��� ��������: " << max_elem << '\n';
//
//		// �������� ������������� �����
//		if (pmax->left && pmax->left->info == max_elem) {
//			delete pmax->left;
//			pmax->left = nullptr;
//		}
//		else if (pmax->right && pmax->right->info == max_elem) {
//			delete pmax->right;
//			pmax->right = nullptr;
//		}
//	}
//	else {
//		std::cout << "������� ��� �������� �� �������.\n";
//	}
//}
//
////int main() {
////	setlocale(LC_ALL, "rus");
////	std::ifstream file("input.txt");
////
////	if (!file.is_open()) {
////		std::cerr << "�� ������� ������� ���� input.txt" << std::endl;
////		return 1;
////	}
////	tree::Tree root = tree::build_from_string(file);
////	file.close();
////	std::cout << "�������� ������:\n";
////	print(root, 0);
////	delete_max_leaf(root);
////	std::cout << "\n������ ����� �������� ������������� �����:\n";
////	print(root, 0);
////	tree::clear(root);
////
////	return 0;
////}
//
