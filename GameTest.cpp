


#include "Game.h"
#include "googletest-main/googletest/include/gtest/gtest.h"
#include "iostream"


TEST(GameTest, AddPlayer)
{
    int numOfGroups = 100;
    int numOfPlayers = 200;
    int scale = 200;
    Game game(numOfGroups, scale);
    
    
    EXPECT_EQ(game.num_of_groups, 100);
    
    for(int i = 1; i <= numOfPlayers; i++){
        game.addPlayer(i+1,i%100,i%200);
    }
    EXPECT_EQ(game.gameGroup.getNumPlayers(),198);
    
    for(int i = 1; i <game.num_of_groups;i++){
        EXPECT_EQ(game.unionGroup.find(i).getNumPlayers(),2);
        //EXPECT_EQ(game.unionGroup.find(i).levelZero.numOfPlayers(),2);
    }
    //for(int i = 0; i < game.num_of_groups; i++){
      //  EXPECT_EQ(game.unionGroup.find(i).getRank());
    //}
    //EXPECT_EQ()
    
    
}

TEST(GameTest, MergeTest)
{
    int numOfGroups = 200;
    int numOfPlayers = 20000;
    int scale = 200;
    Game game(numOfGroups, scale);
    
    int mod = 4;
    for(int i = 1; i <= numOfPlayers; i++){
        int group_id = (i%mod)+1;
        game.addPlayer(i,group_id,group_id);
    }
    EXPECT_EQ(game.unionGroup.find(1).getNumPlayers(),numOfPlayers/mod);
    double percent = 0;
    game.getPercentOfPlayersWithScoreInBounds(0, 1, 0, 1, &percent);
    EXPECT_EQ(percent,100.0/mod);
    
    game.MergeGroups(1,2);
    game.MergeGroups(1,2);
    game.MergeGroups(2,1);
    game.MergeGroups(1,1);
    game.MergeGroups(2,2);
    
    game.getPercentOfPlayersWithScoreInBounds(1, 1, 0, 1, &percent);
    EXPECT_EQ(percent,100.0/2);
    
}


TEST(GameTest, PercentTest)
{
    int numOfGroups = 200;
    int numOfPlayers = 20000;
    int scale = 200;
    Game game(numOfGroups, scale);
    
    int totalPlayersByScore[5][200] = {0};
    int totalPlayers[5] = {0};
    
    int mod = 4;
    for(int level = 1; level <= numOfPlayers; level++){
        int group_id = (level%mod)+1;
        game.addPlayer(level,group_id,group_id);
        game.IncreasePlayerLevel(level, level);
        
        totalPlayers[0]++;
        totalPlayersByScore[0][group_id]++;
        totalPlayers[group_id]++;
        totalPlayersByScore[group_id][group_id]++;
    }
    
    for(int level = 1; level <= numOfPlayers; level++){
        if (level%11 == 0){
            Player* player = game.gameGroup.players.findPlayer(level);
            int group_id = player->group_id;
            totalPlayers[0]--;
            totalPlayersByScore[0][group_id]--;
            totalPlayers[group_id]--;
            totalPlayersByScore[group_id][group_id]--;
            
            game.removePlayer(level);
        }
    }
    game.MergeGroups(1,2);
    for (int score = 0; score < 200; score++) {
        totalPlayersByScore[1][score] += totalPlayersByScore[2][score];
        totalPlayersByScore[2][score] = totalPlayersByScore[1][score];
    }
    totalPlayers[1] += totalPlayers[2];
    totalPlayers[2] = totalPlayers[1];
    
    double percent;
    for (int group_id = 0; group_id <= 4; group_id++) {
        for (int score = 0; score < 10; score++) {
            double ExpectedPercent = 0;
            if (totalPlayers[group_id] > 0){
                ExpectedPercent = double(totalPlayersByScore[group_id][score])/totalPlayers[group_id];
                ExpectedPercent = ExpectedPercent*100.0;
            }
            game.getPercentOfPlayersWithScoreInBounds(group_id, score, 0, numOfPlayers, &percent);
            EXPECT_EQ(ExpectedPercent, percent);
        }
    }
    
    
    
    
}

TEST(GameTest, BoundTest)
{
    int numOfGroups = 200;
    int numOfPlayers = 2000;
    int scale = 200;
    Game game(numOfGroups, scale);
    
    int mod = 4;
    for(int level = 1; level <= numOfPlayers; level++){
        int group_id = (level%mod)+1;
        game.addPlayer(level,group_id,1);
        game.IncreasePlayerLevel(level, level);
        
    }
    for(int level = 1; level <= numOfPlayers; level++){
        if (level%11 == 0){
            game.removePlayer(level);
        }
    }
    game.MergeGroups(1,2);

    
    long levelSum = 0;
    int counter = 0;
    for(int level = numOfPlayers; level >= 1; level--) {
        int group_id = (level % mod) + 1;
        if (group_id != 1 && group_id != 2){
            continue;
        }
        
        if (level%11 != 0){
            counter++;
            levelSum += level;
        }
        int LowerBound, HigherBound;
        double average;
        double ExpectedAverage = double(levelSum)/counter;
        game.GetPlayersBound(1, 1, counter, &LowerBound, &HigherBound);
        EXPECT_EQ(counter, LowerBound);
        EXPECT_EQ(counter, HigherBound);
        game.AverageHighestPlayerLevelByGroup(1, counter, &average);
        EXPECT_EQ(ExpectedAverage, average);
    
    }
    
}









int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}




