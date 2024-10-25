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

	auto j = avl.find(1);
	if (j == avl.end()) {
		std::cout << "didn't found\n";
	}
	else{
		std::cout << *j << '\n';
	}
	std::cout << "Deleted value: "  << avl.pop_min() << "\n";
	avl.dump();
	std::cout << "Deleted value: "  << avl.pop_min() << "\n";
	avl.dump();
	std::cout << "Min: " << avl.min() << "\n";
	std::cout << "Max: " << avl.max() << "\n";
	std::cout << "Deleted value: " << avl.pop_max() << "\n";
	avl.dump();
	return 0;
}
