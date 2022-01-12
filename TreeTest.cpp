
#include "LevelTree.h"
#include "googletest-main/googletest/include/gtest/gtest.h"
#include "iostream"

int dataFunc2(LevelData& data){
    return data.getSubPlayers();
}



TEST(TreeTest, CheckInsert){
    int size = 1000;
    LevelTree levelTree;
    
    for (int level = 0; level < size; level++){
        LevelData data(level);
        levelTree.insert(level, data);
    }
    for (int level = 0; level < size; level++) {
        LevelData* data = levelTree.find(level);
        EXPECT_FALSE(data == nullptr);
        EXPECT_EQ(level, data->getLevel());
    }
    
}

TEST(TreeTest, RankInsertTest){
    int size = 2000;
    LevelTree levelTree;
    
    for (int level = 1; level < size; level++){
        Player player(level, 1, level);
        player.setLevel(level);
        levelTree.insertPlayer(player);
    }
    long levelSum = 0;
    for (int level = 1; level < size; level++) {
        levelSum += level;
        LevelData data = levelTree.getExactLevelData(level);
        EXPECT_EQ(level, data.getLevel());
        EXPECT_EQ(level, data.getLevelSum());
    }
    
}


TEST(TreeTest, RankTest){
    int size = 2000;
    LevelTree levelTree;
    
    for (int level = 1; level < size; level++){
        Player player(level, 1, level);
        player.setLevel(level);
        levelTree.insertPlayer(player);
    }
    for (int level = 1; level < size; level++) {
        LevelData* data = levelTree.find(level);
        EXPECT_FALSE(data == nullptr);
        EXPECT_EQ(level, data->getLevel());
        EXPECT_EQ(level, levelTree.getRank2(level).getLevel());
        EXPECT_EQ(level, levelTree.getRank2(level).getSubPlayers());
        EXPECT_EQ(level, levelTree.getLevelDataRank(level, dataFunc2, false).getSubPlayers());
    
    }
    for (int rm_level = 1900; rm_level > 10; rm_level -= 2) {
        Player player(rm_level, 1, rm_level);
        player.setLevel(rm_level);
        levelTree.removePlayer(player);
        LevelData* data = levelTree.find(rm_level, false);
        EXPECT_FALSE(data == nullptr);
        EXPECT_EQ(rm_level-1, data->getLevel());
        EXPECT_EQ(rm_level-1, levelTree.getRank(rm_level).getLevel());
        EXPECT_EQ(rm_level-1, levelTree.getRank(rm_level).getSubPlayers());
        LevelData dataRank = levelTree.getLevelDataRank(rm_level, dataFunc2, false);
        EXPECT_EQ(rm_level-1, levelTree.getRank(dataRank.getLevel()).getSubPlayers());
        EXPECT_EQ(dataRank.getLevel(), levelTree.getRank(dataRank.getLevel()).getLevel());
    }
    
    
    
}

TEST(TreeTest, CheckInsert2){
    int levels = 2000;
    int PlayersPerLevel = 1;
    LevelTree levelTree;
    int counter = 0;
    return;
    for (int playerPerLevel = 0; playerPerLevel < PlayersPerLevel; playerPerLevel++) {
        for (int level = 0; level < levels; level++) {
            Player player(level, 1, level);
            player.setLevel(level);
            //std::cout << counter++ << std::endl;
            levelTree.insertPlayer(player);
            
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
    return;
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









