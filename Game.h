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
    static const int GameGroupID = -10;
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
        gameGroup.addPlayer(PlayerID, GroupID, score);
        unionGroup.find(GroupID).addPlayer(PlayerID, GroupID, score);
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
        
        gameGroup.addPlayer(player);
        unionGroup.find(player.group_id).addPlayer(player);
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
        
        unionGroup.find(player->group_id).removePlayer(playerID);
        gameGroup.removePlayer(playerID);
        return SUCCESS;
    }
    
    StatusType IncreasePlayerLevel(int PlayerID, int LevelIncrease){
        if (PlayerID <= 0 || LevelIncrease <= 0){
            return INVALID_INPUT;
        }
        Player* player = gameGroup.players.findPlayer(PlayerID);
        if (player == nullptr){
            return  FAILURE;
        }
        Player player_copy = *player;
        //remove
        removePlayer(player_copy.id);
        //increase
        player_copy.increaseLevel(LevelIncrease);
        //Insert
        addPlayer(player_copy);
        return SUCCESS;
    }
    
    StatusType ChangePlayerScore(int PlayerID, int NewScore){
        if (PlayerID <= 0 || NewScore <= 0 || NewScore > scale){
            return INVALID_INPUT;
        }
        Player* player = gameGroup.players.findPlayer(PlayerID);
        if (player == nullptr){
            return FAILURE;
        }
        gameGroup.updatePlayerScore(PlayerID, NewScore);
        unionGroup.find(player->group_id).updatePlayerScore(PlayerID, NewScore);
        //when Allocation Error?
        return SUCCESS;
    }
    
    StatusType getPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel, double * players){
        if(players == nullptr || GroupID < 0 || GroupID > num_of_groups){
            return INVALID_INPUT;
        }
        if (score < 0 || score > scale){
            *players = 0.0;
            return SUCCESS;
        }
        
        if(GroupID == 0){
            *players = gameGroup.getPercentOfPlayersWithScoreInBounds(score, lowerLevel, higherLevel);
        }
        else{
           *players = unionGroup.find(GroupID).getPercentOfPlayersWithScoreInBounds(score, lowerLevel, higherLevel);
        }
        //when Allocation Error?
        return SUCCESS;
    }
    
    StatusType AverageHighestPlayerLevelByGroup(int GroupID, int num_of_players, double *level) {
        if (level == nullptr || GroupID < 0 || GroupID > num_of_groups || num_of_players <= 0) {
            return INVALID_INPUT;
        }
       
        if(GroupID == 0){
            if(num_of_players > gameGroup.getNumPlayers()){
                return FAILURE;
            }
            gameGroup.AverageHighestPlayerLevel(num_of_players, *level);
        }
        else{
            if(num_of_players > unionGroup.find(GroupID).getNumPlayers()){
                return FAILURE;
            }
            unionGroup.find(GroupID).AverageHighestPlayerLevel(num_of_players, *level);
        }
        return SUCCESS;
    }
    StatusType GetPlayersBound(int GroupID, int score, int num_of_players, int *LowerBoundPlayers, int *HigherBoundPlayers){
        if(LowerBoundPlayers == nullptr || HigherBoundPlayers == nullptr || GroupID < 0 || GroupID > num_of_groups
                                        || score <= 0 || score > scale || num_of_players < 0){
            return INVALID_INPUT;
        }
        if(GroupID == 0){
            if(num_of_players > gameGroup.getNumPlayers()){
                return FAILURE;
            }
            gameGroup.GetPlayersBound(score, num_of_players,LowerBoundPlayers,HigherBoundPlayers);
        }
        else{
            if(num_of_players > unionGroup.find(GroupID).getNumPlayers()){
                return FAILURE;
            }
            unionGroup.find(GroupID).GetPlayersBound(score, num_of_players,LowerBoundPlayers,HigherBoundPlayers);
        }
        return SUCCESS;
    }
    
    StatusType MergeGroups(int GroupID1, int GroupID2){
        if(GroupID1 <= 0 || GroupID1 > num_of_groups || GroupID2 <= 0 || GroupID2 > num_of_groups){
            return INVALID_INPUT;
        }
        int group_1 = unionGroup.find((GroupID1)).id;
        int group_2 = unionGroup.find((GroupID2)).id;
        unionGroup.unite(group_1,group_2);
        return SUCCESS;
    }
    
};


#endif //DATA_STRACTURES_WET_2_GAME_H
