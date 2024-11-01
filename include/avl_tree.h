#pragma once 

#include <iostream>
#include <functional>
#include <list>
#define NODE_H(x) (((x)==nullptr)?-1:((x)->height))

template <typename T> class _Avl_node {
	// private:
	public:
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
		void _pop_min(_Avl_node<T>** tree, ListIt* ret_val);
		void _pop_max(_Avl_node<T>** tree, ListIt* ret_val);

	// public:
		_Avl_node(ListIt value, std::list<T>* datalist): _value(value), _datalist(datalist) {};
		ListIt pop_min();
		ListIt pop_max();
		T min();
		T max();
		T get_value() {return *_value;};
		void insert(ListIt value, std::function<int(T, T)> compare_func);
		ListIt find_element(T val, std::function<int(T, T)> compare_func);
		void node_dump(int h);
		void dump();
};

template <typename T> class Avl{
	private: 
		using ListIt = typename std::list<T>::iterator;
		_Avl_node<T>* tree = nullptr;
		std::function<int(T, T)> _compare_func;
		std::list<T> _data_list;
	public:
		Avl(T value, std::function<int(T, T)> compare_func): _compare_func(compare_func) {};
		
		T pop_min() {
			return *(tree->pop_min());
		}
		
		T pop_max() {
			return *(tree->pop_max());
		}

		T min() {
			return tree->min();
		}

		T max() {
			return tree->max();
		}

		int get_count(T min, T max);

		ListIt end(){
			return _data_list.end();
		}

		ListIt begin(){
			return _data_list.begin();
		}

		void insert(T value) {
			_data_list.push_front(value);
			if (tree == nullptr) {
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
T _Avl_node<T>::min() {
	if (NODE_H(this) == 0 || left == nullptr)
		return *_value;
	else
		return left->min();
}

template <typename T>
T _Avl_node<T>::max() {
	if (NODE_H(this) == 0 || right == nullptr)
		return *_value;
	else
		return right->max();
}

template <typename T>
void _Avl_node<T>::_pop_max(_Avl_node<T>** tree, typename std::list<T>::iterator* ret_val) {
	if (NODE_H(*tree) == 0) {
		*ret_val = (*tree)->_value;
		delete *tree;
		*tree = nullptr;
	} else if (NODE_H((*tree)->right) == -1 && NODE_H((*tree)->left) != -1) {
		typename std::list<T>::iterator save_elem = (*tree)->_value;
		(*tree)->_value = (*tree)->left->_value;
		(*tree)->left->_value = save_elem;
		*ret_val = (*tree)->left->_value;

		(*tree)->right = (*tree)->left->right;
		(*tree)->left = (*tree)->left->left;
		delete ((*tree)->left);
		((*tree)->height)--;
	} else {
		if (NODE_H(*tree) != 0)
			_pop_max(&((*tree)->right), ret_val);
		if (NODE_H(*tree) != 0)
			(**tree).update_height();
		if (NODE_H(*tree) != 0)
			(**tree).check_balance();
	}
}

template <typename T>
typename std::list<T>::iterator _Avl_node<T>::pop_max() {
	_Avl_node<T>* avl = this;
	typename std::list<T>::iterator ret_val;
	this->_pop_max(&avl, &ret_val);
	_datalist->erase(ret_val);
	return ret_val;
}

template <typename T>
void _Avl_node<T>::_pop_min(_Avl_node<T>** tree, typename std::list<T>::iterator* ret_val) {
	if (NODE_H(*tree) == 0) {
		*ret_val = (*tree)->_value;
		delete *tree;
		*tree = nullptr;
	} else if (NODE_H((*tree)->left) == -1 && NODE_H((*tree)->right) != -1) {
		typename std::list<T>::iterator save_elem = (*tree)->_value;
		(*tree)->_value = (*tree)->right->_value;
		(*tree)->right->_value = save_elem;
		*ret_val = (*tree)->right->_value;

		(*tree)->left = (*tree)->right->left;
		(*tree)->right = (*tree)->right->right;
		delete ((*tree)->right);
		((*tree)->height)--;
	} else {
		if (NODE_H(*tree) != 0)
			_pop_min(&((*tree)->left), ret_val);
		if (NODE_H(*tree) != 0)
			(**tree).update_height();
		if (NODE_H(*tree) != 0)
			(**tree).check_balance();
	}
}

template <typename T>
typename std::list<T>::iterator _Avl_node<T>::pop_min() {
	_Avl_node<T>* avl = this;
	typename std::list<T>::iterator ret_val;
	this->_pop_min(&avl, &ret_val);
	_datalist->erase(ret_val);	
	return ret_val;
}

template <typename T>
void _Avl_node<T>::insert(ListIt value, std::function<int(T, T)> compare_func) { 
	if (compare_func(*_value, *value) < 0) {
		if (right == nullptr) {
			height = 1;
			right = new _Avl_node(value, _datalist);
		} 
		else 
			right->insert(value, compare_func);
	}
	else if(compare_func(*_value, *value) == 0){
		_datalist->erase(value);
		return;
	}
	else {
		if (left == nullptr) {
			height = 1;
			left = new _Avl_node(value, _datalist);
		} else {
			left->insert(value, compare_func);
		}
	}

	this->update_height();
	this->check_balance();
}

template <typename T>
typename std::list<T>::iterator _Avl_node<T>::find_element(T val, std::function<int(T, T)> compare_func){
	int r = 0;
	for(_Avl_node* node = this; node != nullptr;){
		r = compare_func(*(node->_value), val);
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

template <typename T>
int Avl<T>::get_count(T min, T max){

	if(min > max) {
		T temp = min;
		min = max;
		max = temp;
	}

	std::list<_Avl_node<T>*> queue;
	_Avl_node<T>* current_node;
	queue.push_back(tree);

	int counter = 0;

	while(queue.begin() != queue.end()){
		current_node = *(queue.begin());

		if(current_node == nullptr) {
			queue.pop_front();
			continue;
		}

		// std::cout << "cheking: " << current_node->get_value();	
		if(current_node->get_value() < min) {
			queue.push_back(current_node->right);
			// std::cout << "pushed r\n";
		}
		else if (current_node->get_value() > max){
			queue.push_back(current_node->left);
			// std::cout << "pushed l\n";
		}
		else {
			counter++;
			queue.push_back(current_node->left);
			queue.push_back(current_node->right);
			// std::cout << "pushed both";
		}

		// std::cout << '\n';
		queue.pop_front();
	}
	return counter;
}