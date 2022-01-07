
#include "LevelTree.h"
#include "googletest-main/googletest/include/gtest/gtest.h"






TEST(TreeTest, CheckInit){
    int size = 10;
    UnionFind unionFind(size);
    
    for (int id = 1; id <= size; id++) {
        EXPECT_EQ(id, unionFind.find(id).id);
    }
}







int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}









