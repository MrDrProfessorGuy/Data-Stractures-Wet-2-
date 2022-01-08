
#include "LevelTree.h"
#include "googletest-main/googletest/include/gtest/gtest.h"






TEST(TreeTest, CheckInsert){
    int size = 1000;
    LevelTree levelTree;
    
    for (int level = 0; level < size; level++) {
        LevelData data(level);
        levelTree.insert(level, data);
    }
    for (int level = 0; level < size; level++) {
        LevelData* data = levelTree.find(level);
        EXPECT_FALSE(data == nullptr);
        EXPECT_EQ(level, data->getLevel());
    }
    
}


TEST(TreeTest, CheckRemove){
    int size = 1000;
    LevelTree tree;
    for (int level = 0; level < size; level++) {
        LevelData data(level);
        tree.insert(level, data);
    }
    
    for(int level = 0; level < size; level++){
        if(level % 2 == 0){
            tree.removeNode(level);
        }
    }
    for(int level = 0; level < size; level++){
        if(level % 2 == 0){
            EXPECT_TRUE(tree.exists(level) == false) << "Level = " << level;
        }
    }
}

TEST(TreeTest, checkUpdateData){
    int size = 10;
    LevelTree tree;
    for (int level = 0; level < size; level++) {
        Player player(level, level, level);
        LevelData data(player);
        tree.insert(level, data);
    }
    int level_sum = 0;
    for (int level = 0; level < size; level++) {
        level_sum += level;
        EXPECT_EQ(tree.find(level)->numOfPlayers(), 1) << "Level = " << level;
        EXPECT_EQ(tree.getRank(level).getSubPlayers(), level+1) << "Level = " << level;
        EXPECT_EQ(tree.getRank(level).getLevelSum(), level_sum) << "Level = " << level;
    }
    
    
}


int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}









