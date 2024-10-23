#include <iostream>

void print_elem(int elem) {
	std::cout << elem;
}

int compare(int a, int b) {
	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	return -1;
}

#include "avl_tree.h"

int main() {
	Avl<int> avl(3);
	avl.insert(5);
	avl.insert(6);
	avl.insert(4);
	avl.dump();
	avl.pop();
	avl.dump();
	return 0;
}
