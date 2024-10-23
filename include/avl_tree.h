#pragma once 

#include <iostream>
#include <functional>
#include <list>
#define NODE_H(x) (((x)==nullptr)?-1:((x)->height))


template <typename T> class _Avl_node {
	private:
		using ListIt = typename std::list<T>::iterator;
		
		ListIt _value;
		std::list<T>* _datalist;

		_Avl_node* right = nullptr;
		_Avl_node* left = nullptr;
		int height = 0;

		void update_height();
		void left_rotation();
		void right_rotation();
		void check_balance();
		T left_elem();

	public:
		_Avl_node(ListIt value, std::list<T>* datalist): _value(value), _datalist(datalist) {};
		void pop();
		void insert(ListIt value, std::function<int(T, T)> compare_func);
		typename std::list<T>::iterator find_element(T val, std::function<int(T, T)> compare_func);
		void node_dump(int h);
		void dump();
};

template <typename T> class Avl{
	private: 
		using ListIt = typename std::list<T>::iterator;
		_Avl_node<T>* tree = 0;
		std::function<int(T, T)> _compare_func;
		std::list<T> _data_list;

	public:
		Avl(T value, std::function<int(T, T)> compare_func): _compare_func(compare_func) {};
		
		void pop() {
			tree->pop();
		}

		ListIt end(){
			return _data_list.end();
		}

		ListIt begin(){
			return _data_list.begin();
		}

		void insert(T value) {
			_data_list.push_front(value);
			if(tree == nullptr) {
				tree = new _Avl_node(_data_list.begin(), &_data_list);
			}
			else {
				tree->insert(_data_list.begin(), _compare_func);
			}
		}

		ListIt find(T val) {
			return tree->find_element(val, _compare_func);
		}

		void node_dump(int h) {
			tree->node_dump(h);
		}

		void dump() {
			for(auto &x: _data_list){
				std::cout << x << " ";
			}
			std::cout << '\n';
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
	ListIt save_elem = _value;
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
	ListIt save_elem = _value;
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
		_datalist->erase(_value);
		// _value = _datalist->end();
		// height = -1;
		std::cout << "deleting\n";
		delete this;
		std::cout << "deleted\n";
		return;

	} else if (NODE_H(left) == -1 && NODE_H(right) != -1) {
		ListIt save_elem = _value;
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
void _Avl_node<T>::insert(ListIt value, std::function<int(T, T)> compare_func) { 
	if (compare_func(*_value, *value) <= 0) {
		if (right == nullptr) {
			height = 1;
			right = new _Avl_node(value, _datalist);
		} else 
			right->insert(value, compare_func);
	} else {
		if (left == nullptr) {
			height = 1;
			left = new _Avl_node(value, _datalist);
		} else 
			left->insert(value, compare_func);
	}

	this->update_height();
	this->check_balance();
}

template <typename T>
typename std::list<T>::iterator _Avl_node<T>::find_element(T val, std::function<int(T, T)> compare_func){
	int r = 0;
	for(_Avl_node* node = this; node != nullptr;){
		r = compare_func(*(node->_value), val);
		// std::cout << "comparing " << node->_value << " and " << val << " res: " << r << "\n";
		switch (r)
		{
			case 0: return node->_value;	break;
			case -1: node = node->right; break;
			case 1: node = node->left; break;
			default: std::cout << "error"; return _datalist->end(); //error. aborting
		}
	}
	// std::cout << "didn't found\n";
	return _datalist->end();
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
	
	if (_value != _datalist->end()) {
		print_elem(*_value);
	}
	else {
		std::cout << "bad";
	}

	std::cout << "(" << height << ")\n";
	if (left != nullptr) 
		left->node_dump(h+1);
}