//
// Created by guy cohen on 30/12/2021.
//

#ifndef DATA_STRACTURES_WET_2_GAME_H
#define DATA_STRACTURES_WET_2_GAME_H

#include "HashTable.h"
#include "Group.h"
#include "UnionFind.h"
#include "library2.h"


class Game {

private:
    static const int GameGroupID -10;
public:
    int num_of_groups;
    int scale;
    Group gameGroup;
    UnionFind unionGroup;

    Game(int numOfGroups, int scale) : num_of_groups(numOfGroups), scale(scale),
                                    gameGroup(GameGroupID), unionGroup(num_of_groups){
    
    }
    Game(const Game&) = delete;
    ~Game() = default;
    
    StatusType addPlayer(int PlayerID, int GroupID, int score){
        if (GroupID <= 0 || GroupID > num_of_groups || PlayerID <= 0 ||
            score <= 0 || scale < score){
            return INVALID_INPUT;
        }
        if (gameGroup.players.exists(PlayerID)){
            return FAILURE;
        }
        gameGroup.addPlayer(PlayerID, score);
        Group group = unionGroup.find(GroupID);
        group.addPlayer(PlayerID, score);
        return SUCCESS;
    }
    
    StatusType addPlayer(Player player){
        if (player.group_id <= 0 || player.group_id > num_of_groups || player.id <= 0 ||
            player.score <= 0 || scale < player.score){
            return INVALID_INPUT;
        }
        if (gameGroup.players.exists(player.id)){
            return FAILURE;
        }
        gameGroup.addPlayer(PlayerID, score);
        Group group = unionGroup.find(GroupID);
        group.addPlayer(PlayerID, score);
        return SUCCESS;
    }
    
    StatusType removePlayer(int playerID){
        if (playerID <= 0){
            return INVALID_INPUT;
        }
        Player* player = gameGroup.players.findPlayer(playerID);
        if (player == nullptr){
            return FAILURE;
        }
        Group group = unionGroup.find(player->group_id);
        group.removePlayer(playerID);
        gameGroup.removePlayer(playerID);
        return SUCCESS;
    }
    
    void IncreasePlayerLevel(int PlayerID, int LevelIncrease){
        if (PlayerID <= 0 || LevelIncrease <= 0){
            return;INVALID_INPUT;
        }
        Player* player = gameGroup.players.findPlayer(playerID);
        if (player == nullptr){
            return FAILURE;
        }
        Player player_copy = *player;
        Group group = unionGroup.find(player->group_id);
        //remove
        removePlayer(player_copy.id);
        //increase
        player_copy.increaseLevel(LevelIncrease);
        //Insert
        
        
    }
    
    void ChangePlayerScore(int PlayerID, int NewScore);
    
    void getPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel, double * players);
    
    void AverageHighestPlayerLevelByGroup(int GroupID, int num_of_players, double *level);
    
    void GetPlayersBound(int GroupID, int score, int num_of_players,
                         int *LowerBoundPlayers, int *HigherBoundPlayers);
    
};


#endif //DATA_STRACTURES_WET_2_GAME_H
