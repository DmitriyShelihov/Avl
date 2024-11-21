#include <gtest/gtest.h>
#include "avl_tree.h"

int compare(int a, int b) {
	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	return -1;
}

TEST(test_simple, simple){
    Avl<int> tree{compare};
    for(int i = 0; i < 10; ++i){
        tree.insert(i);
    }

    EXPECT_EQ(tree.get_count(0, 4), 5);
}