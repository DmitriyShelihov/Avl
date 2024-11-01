#include <iostream>
#include <random>

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

	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist100(1,100); // distribution in range [1, 6]

	for(int k = 0; k < 1; k++){
		Avl<int> avl(0, compare);

		int min = dist100(rng);
		int max = dist100(rng);

		if(min > max){
			int tmp = min;
			min = max;
			max = tmp;
		}

		int counter = 0;
		int val = 0;
		for(int i = 0; i < 1000; i ++){
			val = dist100(rng);
			avl.insert(val);
		}

		for(auto x = avl.begin(); x != avl.end(); x++){
			if(min <= (*x) && (*x)<= max) counter++;
		}
		int res = avl.get_count(min, max);

		if(res != counter){
		// if(1){
			avl.dump();
			std::cout << "found " << res << " elements between " << min << " and " << max << " (real counter: "<< counter << ")\n";
		}
	}
	return 0;
}
