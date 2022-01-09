//
// Created by guy cohen on 30/12/2021.
//

#include "Group.h"

// =========================================================================== //
// ============================= Public Methods ============================= //
// =========================================================================== //



Group::Group(int group_id): id(group_id), level_tree(), players(), levelZero(0) {}


void Group::setLevelTree(LevelTree& level_tree){}
void Group::setLevelZero(LevelData& levelZero){}//Maybe useless
void Group::setPlayers(HashTable players){}

int Group::getNumPlayers(){
    return players.curr_amount;
}

void Group::addPlayer(int player_id, int score, int level){
    if (players.exists(player_id)){
        return;
    }
    
    Player new_player(player_id, score, level);
    players.insert(new_player);
    
    if (level == -1){
        levelZero.addNewData(new_player);
    }
    else{
        level_tree.insertPlayer(new_player);
    }
}
void Group::removePlayer(int player_id){
    Player* player = players.findPlayer(player_id);
    if (player == nullptr){
        return;
    }
    
    level_tree.removePlayer(*player);
    players.remove(player_id);
}

void Group::updatePlayerLevel(int player_id, int amount){
    Player* player = players.findPlayer(player_id);
    if (player == nullptr){
        return;
    }

    level_tree.removePlayer(*player);
    player->increaseLevel(amount);
    level_tree.insertPlayer(*player);
}
void Group::updatePlayerScore(int player_id, int amount){
    Player* player = players.findPlayer(player_id);
    if (player == nullptr){
        return;
    }
    
    level_tree.removePlayer(*player);
    player->increaseScore(amount);
    level_tree.insertPlayer(*player);
}
void Group::updatePlayerGroup(int player_id, int group_id){
    Player* player = players.findPlayer(player_id);
    if (player == nullptr){
        return;
    }
    player->setGroupID(group_id);
}

bool Group::merge(Group& group){
    // ===== merge hashTable =====
    int group_size = group.players.size;
    for (int index = 0; index < group_size; index++){
        SortedList<Player>::const_iterator iter = group.players.array->begin();
        SortedList<Player>::const_iterator end = group.players.array->end();
        while (iter != end){
            (*iter).group_id = id;
            players.insert(*iter);
            iter++;
        }
    }
    
    // ===== merge LevelTree =====
    LevelTree::Iterator iter1 = level_tree.firstInOrder();
    LevelTree::Iterator iter2 = group.level_tree.firstInOrder();
    while (*iter2 != nullptr){
        level_tree.insert((*iter2)->getLevel(), *(*iter2));
        iter2++;
    }
    return true;
}

int dataFunc(LevelData& data){
    return data.getSubPlayers();
}

LevelData Group::getRank(int level, bool& levelFound){
    LevelData level_rank(level);
    levelFound = true;
    
    if (level == -1){
        return levelZero;
    }
    else{
        if (!level_tree.exists(level)){
            levelFound = false;
        }
        return (level_tree.getRank(level,false));
    }

}
bool Group::getTopPlayersStats(int num_of_players, LevelData &Remainder, LevelData &quotient){
    LevelData *level_data;
    
    LevelData higher_bound = getGroupRank();
    if(higher_bound == LevelData(INVALID_LEVEL)){
        return false;//Failure
    }

    int total_players = higher_bound.getSubPlayers();
    if(num_of_players > total_players){
        return false;//Failure
    }
    else if(num_of_players == total_players){
        quotient = higher_bound;
    }
    
    int target_num_players = total_players - num_of_players;
    LevelData lower_bound = level_tree.getLevelDataRank(target_num_players,dataFunc,false);
    if (lower_bound.getSubPlayers() == target_num_players){
        quotient = higher_bound - lower_bound;
    }
    else{
        LevelTree::Iterator remainder_iter = level_tree.findIter(Remainder.getLevel());
        remainder_iter++;
        
        quotient = *(*remainder_iter) - higher_bound;
        Remainder = lower_bound - *(*remainder_iter);
    }
    return true;//Success
}


double Group::getPercentOfPlayersWithScoreInBounds(int score, int lowerLevel, int higherLevel){
    bool level_found = true;
    LevelData lower_rank = getRank(lowerLevel, level_found);
    LevelData higher_rank = getRank(higherLevel, level_found);
    
    double players_with_score = higher_rank.getScoreHist()[score] - lower_rank.getScoreHist()[score];
    double total_players = higher_rank.getSubPlayers() - lower_rank.getSubPlayers();
    return (players_with_score/total_players);
}

bool Group::AverageHighestPlayerLevel(int num_of_players, double &level){
    LevelData remainder(INVALID_LEVEL);
    LevelData quotient(INVALID_LEVEL);
    if (!getTopPlayersStats(num_of_players, remainder, quotient)){
        return false;
    }
    double level_sum = quotient.getLevelSum() + remainder.getLevelSum();
    level = level_sum/num_of_players;
    return true;
}

bool Group::GetPlayersBound(int score, int num_of_players, int *LowerBoundPlayers, int *HigherBoundPlayers){
    
    LevelData remainder(INVALID_LEVEL);
    LevelData quotient(INVALID_LEVEL);
    if (!getTopPlayersStats(num_of_players, remainder, quotient)){
        return false;
    }
    *LowerBoundPlayers = quotient.getScoreHist()[score];
    int score_remainder = remainder.getScoreHist()[score];
    int remaining_players = num_of_players - quotient.getSubPlayers();
    if (remaining_players < score_remainder){
        score_remainder = remaining_players;
    }
    *HigherBoundPlayers = *LowerBoundPlayers;
    *LowerBoundPlayers = *LowerBoundPlayers + score_remainder;
    return true;
}

// =========================================================================== //
// ============================= Private Methods ============================= //
// =========================================================================== //

LevelData Group::getLevelData(int level){
    if (level == -1){
        return levelZero;
    }
    else{
        LevelData* data = level_tree.find(level);
        if (data != nullptr){
            ((*data).mergeSubLevelData(levelZero, true));
            return *data;
        }
        return levelZero;
    }
}

LevelData Group::getGroupRank(){
    if (*level_tree.root() == nullptr){
        if (levelZero.numOfPlayers() > 0){
            return levelZero;
        }
        return LevelData(INVALID_LEVEL);
    }
    else{
        return getLevelData((*level_tree.root())->getLevel());
    }
}