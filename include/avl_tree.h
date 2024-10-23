#pragma once 

#include <iostream>
#include <functional>
#define NODE_H(x) (((x)==nullptr)?-1:((x)->height))


template <typename T> class _Avl_node {
	private:
		T _value;
		_Avl_node* right = nullptr;
		_Avl_node* left = nullptr;
		int height = 0;

		void update_height();
		void left_rotation();
		void right_rotation();
		void check_balance();
		T left_elem();

	public:
		_Avl_node(T value) : _value(value) {}
		void pop();
		void insert(T value, std::function<int(T, T)> compare_func);
		T* find_element(T val, std::function<int(T, T)> compare_func);
		void node_dump(int h);
		void dump();
};

template <typename T> class Avl{
	private: 
		_Avl_node<T>* tree;
		std::function<int(T, T)> _compare_func;

	public:
		Avl(T value, std::function<int(T, T)> compare_func): _compare_func(compare_func) 
		{
			tree = new _Avl_node(value);
		};
		
		void pop() {
			tree->pop();
		}

		void insert(T value) {
			tree->insert(value, _compare_func);
		}

		T* find_element(T val) {
			return tree->find_element(val, _compare_func);
		}

		void node_dump(int h) {
			tree->node_dump(h);
		}

		void dump() {
			tree->dump();
		}
};


template <typename T>
void _Avl_node<T>::update_height(){
	{
		if (NODE_H(left) >= NODE_H(right)) {
			height = NODE_H(left)+1;
		} else {
			height = NODE_H(right)+1;
		}
	}
}

template <typename T>
void _Avl_node<T>::left_rotation() {
	T save_elem = _value;
	_value = right->_value;
	right->_value = save_elem;

	_Avl_node* save_tree = left;
	left = right;
	right = right->right;

	left->right = left->left;
	left->left = save_tree;

	left->update_height();
	this->update_height();
}

template <typename T>
void _Avl_node<T>::right_rotation() {
	T save_elem = _value;
	_value = left->_value;
	left->_value = save_elem;

	_Avl_node* save_tree = right;

	right = left;
	left = left->left;

	right->left = right->right;
	right->right = save_tree;

	right->update_height();
	this->update_height();
}	

template <typename T>
void _Avl_node<T>::check_balance() {
	if (NODE_H(right)-NODE_H(left) == -2) {
		if (NODE_H(left->right) - NODE_H(left->left) == 1)
			left->left_rotation();
		this->right_rotation();
	} else if (NODE_H(right) - NODE_H(left) == 2) {
		if (NODE_H(right->right)-NODE_H(right->left) == -1)
			right->right_rotation();
		this->left_rotation();
	}
}

template <typename T>
T _Avl_node<T>::left_elem() {
	if (NODE_H(this) == 0 || left == nullptr)
		return _value;
	else
		return left->left_elem();
}


template <typename T>
void _Avl_node<T>::pop() {
	if (height == 0) {
		delete &_value;
		height = -1;
		return;
	} else if (NODE_H(left) == -1 && NODE_H(right) != -1) {
		T save_elem = _value;
		_value = right->_value;
		right->_value = save_elem;

		delete left;

		left = right->left;
		right = right->right;

		height--;
	} else {
		if (NODE_H(this) != 0)
			left->pop();
		if (NODE_H(this) != 0)
			this->update_height();
		if (NODE_H(this) != 0)
			this->check_balance();
	}
}

template <typename T>
void _Avl_node<T>::insert(T value, std::function<int(T, T)> compare_func) { 
	if (compare_func(_value, value) <= 0) {
		if (right == nullptr) {
			height = 1;
			right = new _Avl_node(value);
		} else 
			right->insert(value, compare_func);
	} else {
		if (left == nullptr) {
			height = 1;
			left = new _Avl_node(value);
		} else 
			left->insert(value, compare_func);
	}

	this->update_height();
	this->check_balance();
}

template <typename T>
T* _Avl_node<T>::find_element(T val, std::function<int(T, T)> compare_func){
	int r = 0;
	for(_Avl_node* node = this; node != nullptr;){
		r = compare_func(node->_value, val);
		// std::cout << "comparing " << node->_value << " and " << val << " res: " << r << "\n";
		switch (r)
		{
			case 0: return &(node->_value);	break;
			case -1: node = node->right; break;
			case 1: node = node->left; break;
			default: std::cout << "error"; return nullptr; //error. aborting
		}
	}
	// std::cout << "didn't found\n";
	return nullptr;
}

template <typename T>
void _Avl_node<T>::dump()
 {
	std::cout << "Avl:\n";
	this->node_dump(0);
}

template <typename T>
void _Avl_node<T>::node_dump(int h) {
	if (right != nullptr)
		right->node_dump(h+1);
	for (int i = 0; i < h; ++i) {
		std::cout << "          ";
	}
	print_elem(_value);
	std::cout << "(" << height << ")\n";
	if (left != nullptr) 
		left->node_dump(h+1);
}