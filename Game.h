//
// Created by guy cohen on 30/12/2021.
//

#ifndef DATA_STRACTURES_WET_2_GAME_H
#define DATA_STRACTURES_WET_2_GAME_H

#include "HashTable.h"
#include "Group.h"
#include "UnionFind.h"


class Game {

private:

public:
    int scale;
    Group gameGroup;
    UnionFind unionGroup;

    Game();
    Game(const Game&) = delete;
    ~Game();
    
    void addPlayer(int PlayerID, int GroupID, int score);
    
    void removePlayer(int playerID);
    
    void IncreasePlayerLevel(int PlayerID, int LevelIncrease);
    
    void ChangePlayerScore(int PlayerID, int NewScore);
    
    void getPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel, double * players);
    
    void AverageHighestPlayerLevelByGroup(int GroupID, int num_of_players, double *level);
    
    void GetPlayersBound(int GroupID, int score, int num_of_players,
                         int *LowerBoundPlayers, int *HigherBoundPlayers);
    
};


#endif //DATA_STRACTURES_WET_2_GAME_H
