


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











int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}




