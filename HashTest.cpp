
#include "HashTable.h"
#include "googletest-main/googletest/include/gtest/gtest.h"


TEST(HashTest, Init){
    HashTable hash;
    for(int i = 0; i < 100; i++){
        Player player(i,0,0);
        hash.insert(player);
    }
    //hash.printHash();
    EXPECT_EQ(hash.size, 128);
    
}

TEST(HashTest, GrowAndShrinkCheck){
    HashTable hashTable;
    int num_of_players = 10000;
    int theoreticalSize = 2;
    int counter = 0;
    
    for (int player_id = 0; player_id < num_of_players; player_id++) {
        Player current_player(player_id, 0);
        hashTable.insert(current_player);
        if (counter == theoreticalSize){
            theoreticalSize *= 4;
        }
        counter++;
        EXPECT_EQ(counter, hashTable.curr_amount);
        EXPECT_EQ(theoreticalSize, hashTable.size);
    }
    
    for (int player_id = num_of_players-1; player_id >= 0; player_id--) {
        hashTable.remove(player_id);
        counter--;
        if (counter == theoreticalSize/(16)){
            theoreticalSize /= 4;
        }
        EXPECT_EQ(counter, hashTable.curr_amount);
        EXPECT_EQ(theoreticalSize, hashTable.size);
    }
}


TEST(HashTest, AddRemoveCheck){
    HashTable hashTable;
    int num_of_players = 10000;
    int counter = 0;
    
    for (int player_id = 0; player_id < num_of_players; player_id++) {
        Player current_player(player_id, 0);
        hashTable.insert(current_player);
        counter++;
        EXPECT_EQ(true, hashTable.exists(player_id));
    }
    
    for (int player_id = num_of_players-1; player_id >= 0; player_id--) {
        hashTable.remove(player_id);
        counter--;
        EXPECT_EQ(false, hashTable.exists(player_id));
    }
}


TEST(HashTest, find){
    HashTable hash;
    
    for(int i = 0; i < 100; i++){
        Player player(i,0,0);
        hash.insert(player);
    }
    for(int i = 150; i > 0; i--){
        if(i > 99){
            EXPECT_EQ(hash.exists(i), false);
        }
        else{
            EXPECT_EQ(hash.exists(i), true);
        }
    }
}

TEST(HashTest, Insert){
    HashTable hash;
    
    for(int i = 0; i < 100; i++){
        Player player1(i,0,0);
        Player player2(i+hash.size,0,0);
        hash.insert(player1);
        hash.insert(player2);
        EXPECT_EQ(hash.array[i].length(), 2);
        hash.printHash(i);
    }
    
    
    
}

int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


