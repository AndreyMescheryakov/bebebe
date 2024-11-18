#include <iostream>
#include <fstream>
#include "BinTree.h"

// Функция для построения дерева из строки
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
    // Чтение дерева из файла input.txt
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    std::string data;
    infile >> data;
    infile.close();

    int pos = 0;
    BinTree tree;
    tree.root = buildTree(data, pos);

    std::cout << "Структура дерева до удаления:" << std::endl;
    tree.print();

    // Выбор функции удаления
    int choice;
    std::cout << "Выберите метод удаления максимального листа:\n";
    std::cout << "1. Рекурсивный метод\n";
    std::cout << "2. Итеративный метод\n";
    std::cout << "Введите номер метода (1 или 2): ";
    std::cin >> choice;

    if (choice == 1) {
        // Вызов рекурсивной функции
        tree.deleteMaxLeafRecursively();
        std::cout << "Максимальный лист удален рекурсивно." << std::endl;
    }
    else if (choice == 2) {
        // Вызов итеративной функции и получение родителя удаленного узла
        Node* pmax = tree.deleteMaxLeafIteratively();

        if (pmax) {
            std::cout << "Родитель удаленного максимального листа: " << pmax->data << std::endl;
        }
        else {
            std::cout << "Максимальный лист — это корень дерева, или дерево пусто." << std::endl;
        }
    }
    else {
        std::cerr << "Неверный выбор. Пожалуйста, перезапустите программу и введите 1 или 2." << std::endl;
        return 1;
    }

    // Печать структуры дерева после удаления
    std::cout << "Структура дерева после удаления максимального листа:" << std::endl;
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
//			return nullptr; // Пустой узел
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
//// Задача: найти родителя и удалить максимальный элемент - лист
//
//void task6_rec(tree::Tree& t, tree::Tree& pmax, TInfo& max_elem) {
//	if (t) {
//		// Ищем левый лист, проверяем нужно ли обновить максимум
//		if (t->left && tree::is_leaf(t->left) && (!pmax || t->left->info > max_elem)) {
//			max_elem = t->left->info;
//			pmax = t;
//		}
//		// Ищем правый лист, проверяем нужно ли обновить максимум
//		if (t->right && tree::is_leaf(t->right) && (!pmax || t->right->info > max_elem)) {
//			max_elem = t->right->info;
//			pmax = t;
//		}
//		// Рекурсивно обходим дерево
//		task6_rec(t->left, pmax, max_elem);
//		task6_rec(t->right, pmax, max_elem);
//	}
//}
///*
//void task6_iter(tree::Tree t, tree::Tree& pmax, TInfo& max_elem) {
//	if (!t) return;
//
//	std::stack<tree::Tree> node_stack;   // Стек для обхода узлов
//	std::stack<tree::Tree> parent_stack; // Стек для хранения родителей узлов
//
//	node_stack.push(t);
//	parent_stack.push(nullptr);
//
//	while (!node_stack.empty()) {
//		tree::Tree current = node_stack.top();
//		tree::Tree parent = parent_stack.top();
//		node_stack.pop(); // Удаляем из стека так как сейчас обрабатываются
//		parent_stack.pop();
//
//		if (tree::is_leaf(current)) {
//			// Если текущий узел — лист, обновляем максимум, если нужно
//			if (!pmax || current->info > max_elem) {
//				max_elem = current->info;
//				pmax = parent;
//			}
//		}
//		else {
//			// Если у текущего узла есть правый потомок, добавляем его в стек
//			if (current->right) {
//				node_stack.push(current->right);
//				parent_stack.push(current);
//			}
//			// Если у текущего узла есть левый потомок, добавляем его в стек
//			if (current->left) {
//				node_stack.push(current->left);
//				parent_stack.push(current);
//			}
//		}
//	}
//}
//*/
//
////Сделат саму функцию Tree и чтобы возвращать pmax
//void task6_iter(tree::Tree t, tree::Tree& pmax, TInfo& max_elem) {
//	std::stack<tree::Tree> s; // Стек для хранения правых потомков
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
//			// Если есть и правый потомок, добавляем его в стек
//			if (t->right) {
//				s.push(t->right);
//			}
//			// Переходим к левому потомку, обновляем родителя
//			parent = t;
//			t = t->left;
//		}
//		// Если левого потомка нет, но есть правый, переходим к правому
//		else {
//			if (t->right) {
//				parent = t;
//				t = t->right;
//			}
//			// Если нет ни левого, ни правого потомка, переходим к узлу из стека
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
////	<обработка t->info>
////		if (t->left) {
////			if (t->right) {
////				s.push(t->right)
////			t = t->left
////			}
////		}
////		else {
////			if (t->right)
////				t = t->right
////			else//нет ни левого ни правого
////				if (!stack.empty())
////					t = s.top(); s.pop();
////				else t = nullptr;
////		}
////}
//
//void delete_max_leaf(tree::Tree& t) {
//	if (!t) return;
//
//	tree::Tree pmax = nullptr; // Родитель максимального листа
//	TInfo max_elem = '\0';     // Максимальный элемент среди листьев, изначально пустой символ
//
//	// Рекурсивный обход для поиска максимального листа
//	/*
//	task6_rec(t, pmax, max_elem);  // Рекурсивный поиск максимального листа
//	*/
//
//	// Итеративный обход для поиска максимального листа 
//	task6_iter(t, pmax, max_elem);  // Итеративный поиск максимального листа
//
//	// Проверка и вывод информации о максимальном листе перед удалением
//	if (pmax) {
//		std::cout << "Максимальный лист для удаления: " << max_elem << '\n';
//
//		// Удаление максимального листа
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
//		std::cout << "Листьев для удаления не найдено.\n";
//	}
//}
//
////int main() {
////	setlocale(LC_ALL, "rus");
////	std::ifstream file("input.txt");
////
////	if (!file.is_open()) {
////		std::cerr << "Не удалось открыть файл input.txt" << std::endl;
////		return 1;
////	}
////	tree::Tree root = tree::build_from_string(file);
////	file.close();
////	std::cout << "Исходное дерево:\n";
////	print(root, 0);
////	delete_max_leaf(root);
////	std::cout << "\nДерево после удаления максимального листа:\n";
////	print(root, 0);
////	tree::clear(root);
////
////	return 0;
////}
//
