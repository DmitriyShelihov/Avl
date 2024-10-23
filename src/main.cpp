#include <iostream>

void print_elem(int elem) {
	std::cout << elem;
}

#include "avl_tree.h"

int compare(int a, int b) {
	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	return -1;
}


int main() {
	Avl<int> avl(0, compare);

	for(int i = 1; i < 10; i ++){
		avl.insert(i);
	}
	avl.dump();

	int* j = avl.find_element(5);
	if (j == nullptr) {
		std::cout << "didn't found\n";
	}
	else{
		std::cout << *j << '\n';
	}
	
	return 0;
}
