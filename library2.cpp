
#include "library2.h"
#include "Game.h"




void *Init(int k, int scale){
    return new Game(k, scale);
}

StatusType MergeGroups(void *DS, int GroupID1, int GroupID2){
    if (DS == nullptr){
        return INVALID_INPUT;
    }
    Game* game = (Game*)DS;
    return game->MergeGroups(GroupID1, GroupID2);
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score){
    if (DS == nullptr){
        return INVALID_INPUT;
    }
    Game* game = (Game*)DS;
    return game->addPlayer(PlayerID, GroupID, score);
}

StatusType RemovePlayer(void *DS, int PlayerID){
    Game* game = (Game*)DS;
    if(game == nullptr){
        return  INVALID_INPUT;
    }
    return game->removePlayer(PlayerID);
}

StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease){
    Game* game = (Game*)DS;
    if(game == nullptr){
        return  INVALID_INPUT;
    }
    return game->IncreasePlayerLevel(PlayerID,LevelIncrease);
}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore){
    if (DS == nullptr){
        return INVALID_INPUT;
    }
    Game* game = (Game*)DS;
    return game->ChangePlayerScore(PlayerID, NewScore);
}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                                double * players){
    if (DS == nullptr){
        return INVALID_INPUT;
    }
    if (lowerLevel > higherLevel){
        return FAILURE;
    }
    Game* game = (Game*)DS;
    return game->getPercentOfPlayersWithScoreInBounds(GroupID, score, lowerLevel, higherLevel, players);
}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double * level){
    Game* game = (Game*)DS;
    if(game == nullptr){
        return  INVALID_INPUT;
    }
    return game->AverageHighestPlayerLevelByGroup(GroupID,m,level);
}

StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,
                           int * LowerBoundPlayers, int * HigherBoundPlayers){
    Game* game = (Game*)DS;
    if(game == nullptr){
        return  INVALID_INPUT;
    }
    return game->GetPlayersBound(GroupID,score,m,LowerBoundPlayers,HigherBoundPlayers);
}

void Quit(void** DS){
    Game** game = (Game**)DS;
    delete *game;
    *DS = nullptr;
}













