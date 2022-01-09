
#include "googletest-main/googletest/include/gtest/gtest.h"
#include "iostream"
#include "Group.h"







TEST(GroupTest, AddPlayer){
    int numOfPlayers = 1000;
    int maxLevel = 10;
    Group group(1);
    
    for (int player_id = 0; player_id < numOfPlayers; player_id++) {
        group.addPlayer(player_id, player_id);
    }
    for (int player_id = 0; player_id < numOfPlayers; player_id++) {
        int higher = 1;
        int lower = 10;
        double tmp = group.getPercentOfPlayersWithScoreInBounds(5, lower, higher);
        EXPECT_EQ((1.0/(higher-lower+1)), tmp);
        
    }
    
}




int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
    
}




