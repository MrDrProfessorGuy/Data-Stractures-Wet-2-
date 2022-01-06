

#include "UnionFind.h"
#include "googletest-main/googletest/include/gtest/gtest.h"


TEST(UnionTestt, CheckInit){
    int size = 10;
    UnionFind unionFind(size);
    
    for (int id = 1; id <= size; id++) {
        EXPECT_EQ(id, unionFind.find(id).id);
    }
}

TEST(UnionTestt, Unite2Groups){
    int size = 10;
    UnionFind unionFind(size);
    unionFind.unite(1,2);
    
    EXPECT_EQ(unionFind.find(1).id, unionFind.find(2).id);
}

TEST(UnionTestt, UniteAll){
    int size = 10000;
    UnionFind unionFind(size);
    for (int i = 1; i < size; i++) {
        unionFind.unite(i, i+1);
        EXPECT_EQ(unionFind.find(i).id, unionFind.find(i+1).id);
    }
}

TEST(UnionTestt, ReverseUniteAll){
    int size = 10000;
    UnionFind unionFind(size);
    for (int i = size; i > 1; i--) {
        unionFind.unite(i, i-1);
        EXPECT_EQ(unionFind.find(i).id, unionFind.find(i-1).id);
    }
}

TEST(UnionTestt, UniteAllEven){
    int size = 10000;
    UnionFind unionFind(size);
    for (int i = 2; i <= size; i += 2) {
        unionFind.unite(2, i);
    }
    for (int i = 1; i <= size; i++) {
        if (i%2 == 0){
            EXPECT_EQ(unionFind.find(2).id, unionFind.find(i).id);
        }
        else{
            EXPECT_EQ(i, unionFind.find(i).id);
        }
    }
}
TEST(UnionTestt, UniteByEvenOrNot){
    int size = 10000;
    UnionFind unionFind(size);
    for (int i = 3; i <= size; i++) {
        if (i%2 == 0){
            unionFind.unite(i-2, i);
        }
        else{
            unionFind.unite(i-2, i);
        }
        
    }
    for (int i = 1; i <= size; i++) {
        if (i%2 == 0){
            EXPECT_EQ(unionFind.find(2).id, unionFind.find(i).id);
        }
        else{
            EXPECT_EQ(unionFind.find(1).id, unionFind.find(i).id);
        }
    }
}

int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
















