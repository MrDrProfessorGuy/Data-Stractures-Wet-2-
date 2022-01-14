
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


TEST(TreeTest, InsertRemoveTest){
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




int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}









