#include <iostream>
#include <set>
#include "avl_tree.h"

int compare(int a, int b) {
	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	return -1;
}

int main(){
    Avl<int> avl(compare);
    int val1, val2 = 0;
    char command = '\0';
    
    while (std::cin.good()){
        command = '\0';
        std::cin >> command;

        if (command == 'k'){
            std::cin >> val1;
            avl.insert(val1);
        }
        else if (command == 'q'){
            std::cin >> val1 >> val2;

            if (val1 > val2){
                std::cout << 0 << ' ';
            }
            else {
                std::cout << avl.get_count(val1, val2) << ' ';
            }
        }
        else {
            break;
        }
    }
    std::cout << '\n';
    return 0;
}
