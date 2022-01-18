
#include "library2.h"
#include "Game.h"



void *Init(int k, int scale){
    return new Game(k, scale);
}

StatusType MergeGroups(void *DS, int GroupID1, int GroupID2){
    try {
        if (DS == nullptr){
            return INVALID_INPUT;
        }
        Game* game = (Game*)DS;
        return game->MergeGroups(GroupID1, GroupID2);
    }
    catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score){
    try {
        if (DS == nullptr){
            return INVALID_INPUT;
        }
        Game* game = (Game*)DS;
        return game->addPlayer(PlayerID, GroupID, score);
    }
    catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
}

StatusType RemovePlayer(void *DS, int PlayerID){
    try {
        Game* game = (Game*)DS;
        if(game == nullptr){
            return  INVALID_INPUT;
        }
        return game->removePlayer(PlayerID);
    }
    catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
}

StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease){
    try {
        Game* game = (Game*)DS;
        if(game == nullptr){
            return  INVALID_INPUT;
        }
        return game->IncreasePlayerLevel(PlayerID,LevelIncrease);
    }
    catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore){
    try {
        if (DS == nullptr){
            return INVALID_INPUT;
        }
        Game* game = (Game*)DS;
        return game->ChangePlayerScore(PlayerID, NewScore);
    }
    catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                                double * players){
    try {
        if (DS == nullptr){
            return INVALID_INPUT;
        }
        if (lowerLevel > higherLevel){
            return FAILURE;
        }
        Game* game = (Game*)DS;
        return game->getPercentOfPlayersWithScoreInBounds(GroupID, score, lowerLevel, higherLevel, players);
    }
    catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double * level){
    try {
        Game* game = (Game*)DS;
        if(game == nullptr){
            return  INVALID_INPUT;
        }
        return game->AverageHighestPlayerLevelByGroup(GroupID,m,level);
    }
    catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
}

StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,
                           int * LowerBoundPlayers, int * HigherBoundPlayers){
    try {
        Game* game = (Game*)DS;
        if(game == nullptr){
            return  INVALID_INPUT;
        }
        return game->GetPlayersBound(GroupID,score,m,LowerBoundPlayers,HigherBoundPlayers);
    }
    catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
}

void Quit(void** DS){
    Game** game = (Game**)DS;
    delete *game;
    *DS = nullptr;
}













