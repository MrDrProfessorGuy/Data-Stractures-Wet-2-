
#include "LevelTree.h"
#include "googletest-main/googletest/include/gtest/gtest.h"
#include "iostream"





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

TEST(TreeTest, CheckInsert2){
    int levels = 2000;
    int PlayersPerLevel = 4;
    LevelTree levelTree;
    int counter = 0;
    
    for (int playerPerLevel = 0; playerPerLevel < PlayersPerLevel; playerPerLevel++) {
        for (int level = 0; level < levels; level++) {
            Player player(level, level, level);
            levelTree.insertPlayer(player);
            std::cout << counter++ << std::endl;
        }
    }
    
    for (int level = 0; level < levels; level++) {
        LevelData* data = levelTree.find(level);
        LevelData exact = levelTree.getExactLevelData(level);
        EXPECT_FALSE(data == nullptr);
        EXPECT_EQ(level, data->getLevel());
        EXPECT_EQ(PlayersPerLevel, exact.getSubPlayers());
        EXPECT_EQ(PlayersPerLevel, exact.getScoreHist()[level]);
        EXPECT_EQ(exact.getSubPlayers()*level, exact.getLevelSum());
    
    }
    
}


TEST(TreeTest, CheckRemove0){
    int size = 1000;
    LevelTree tree;
    for (int level = 0; level < size; level++) {
        Player player(level, 1, level);
        tree.insertPlayer(player);
    }
    
    for(int level = 0; level < size; level++){
        if(level % 2 == 0){
            Player player(level, 1, level);
            tree.removePlayer(player);
        }
    }
    for(int level = 0; level < size; level++){
        if(level % 2 == 0){
            EXPECT_FALSE((tree.exists(level))) << "Level = " << level;
        }
    }
}

TEST(TreeTest, checkUpdateData){
    int size = 0;
    LevelTree tree;
    for (int tmp_level = 0; tmp_level < size; tmp_level++) {
        int level = tmp_level;
        
        Player player(level, level, level);
        //LevelData data(player);
        //tree.insert(level, data);
        std::cout << "============== Level = " << tmp_level << " ==============" << std::endl;
    }
    int level_sum = 0;
    for (int level = 0; level < size; level++) {
        level_sum += level;
        //std::cout << "============== Level = " << level << " ==============" << std::endl;
        //EXPECT_EQ(tree.find(level)->numOfPlayers(), 1);
        
        //EXPECT_EQ(tree.getRank(level).getSubPlayers(), level+1);
        //EXPECT_EQ(tree.getRank(level).getLevelSum(), level_sum);
    }
    
    
}


int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}









