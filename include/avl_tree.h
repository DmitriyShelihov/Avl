#pragma once 

#include <iostream>
#define NODE_H(x) (((x)==nullptr)?-1:((x)->height))

template <typename T> class Avl {
	private:
		T _value;
		Avl* right = nullptr;
		Avl* left = nullptr;
		int height = 0;

	public:
		Avl(T value) : _value(value) {}
		
		void update_height() {
			if (NODE_H(left) >= NODE_H(right)) {
				height = NODE_H(left)+1;
			} else {
				height = NODE_H(right)+1;
			}
		}

		void left_rotation() {
			T save_elem = _value;
			_value = right->_value;
			right->_value = save_elem;

			Avl* save_tree = left;
			left = right;
			right = right->right;

			left->right = left->left;
			left->left = save_tree;

			left->update_height();
			this->update_height();
		}

		void right_rotation() {
			T save_elem = _value;
			_value = left->_value;
			left->_value = save_elem;

			Avl* save_tree = right;

			right = left;
			left = left->left;

			right->left = right->right;
			right->right = save_tree;

			right->update_height();
			this->update_height();
		}	

		void check_balance() {
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

		void insert(T value) { 
			if (compare(_value, value) <= 0) {
				if (right == nullptr) {
					height = 1;
					right = new Avl(value);
				} else 
					right->insert(value);
			} else {
				if (left == nullptr) {
					height = 1;
					left = new Avl(value);
				} else 
					left->insert(value);
			}

			this->update_height();
			this->check_balance();
		}
		
		void pop() {
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

		T left_elem() {
			if (NODE_H(this) == 0 || left == nullptr)
				return _value;
			else
				return left->left_elem();
		}
		
		T* find_element(T val){
			int r = 0;
			for(Avl* node = this; node != nullptr;){
				r = compare(node->_value, val);
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

		void node_dump(int h) {
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



		void dump() {
			std::cout << "Avl:\n";
			this->node_dump(0);
		}
};
