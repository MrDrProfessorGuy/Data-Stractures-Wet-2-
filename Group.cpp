//
// Created by guy cohen on 30/12/2021.
//

#include "Group.h"

// =========================================================================== //
// ============================= Public Methods ============================= //
// =========================================================================== //



Group::Group(int group_id): id(group_id), level_tree(), players(), levelZero(0) {}

Group::~Group() {}

void Group::setLevelTree(LevelTree& level_tree){}
void Group::setLevelZero(LevelData& levelZero){}//Maybe useless
void Group::setPlayers(HashTable players){}

void Group::addPlayer(int player_id, int score, int level){
    if (players.exists(player_id)){
        return;
    }
    
    Player new_player(player_id, score, level);
    players.insert(new_player);
    
    if (level == 0){
        levelZero.addNewData(new_player);
    }
    else{
        LevelData* level_data = level_tree.find(level);
        if (level_data == nullptr){
            LevelData data(level);
            data.addNewData(new_player);
            level_tree.insert(level, data);
        }
        else{
            level_tree.insert(level, *level_data);
        }
    }
}
void Group::removePlayer(int player_id){
    if (!players.exists(player_id)){
        return;
    }
    Player player = players.find(player_id);
    
    LevelData* level_data = getLevelData(player.level);
    level_data->removeData(player);
    
    players.remove(player_id);
}

void Group::updatePlayerLevel(int player_id, int new_level){
    if (!players.exists(player_id)){
        return;
    }
    Player player = players.find(player_id);
    
    LevelData* level_data = getLevelData(player.level);
    level_data->removeData(player);
    
    player.setLevel(new_level);
    level_data->addNewData(player);
}
void Group::updatePlayerScore(int player_id, int new_score){
    if (!players.exists(player_id)){
        return;
    }
    Player player = players.find(player_id);
    
    LevelData* level_data = getLevelData(player.level);
    level_data->removeData(player);
    
    player.setScore(new_score);
    level_data->addNewData(player);
}
void Group::updatePlayerGroup(int player_id, int group_id){
    if (!players.exists(player_id)){
        return;
    }
    Player player = players.find(player_id);
    player.setGroupID(group_id);
}

bool Group::merge(Group& group){
    // ===== merge hashTable =====
    int group_size = group.players.size;
    for (int index = 0; index < group_size; index++){
        SortedList<Player>::const_iterator iter = group.players.Array.begin();
        SortedList<Player>::const_iterator end = group.players.Array.end();
        while (iter != end){
            (*iter).group_id = id;
            players.insert(*iter);
            iter++;
        }
    }
    
    // ===== merge LevelTree =====
    LevelTree::Iterator iter1 = level_tree.firstInOrder();
    LevelTree::Iterator iter2 = group.level_tree.firstInOrder();
    
    
    
}

int dataFunc(LevelData& data){
    return data.getSubPlayers();
}


LevelData Group::getRank(int level, bool& levelFound){
    LevelData level_rank(level);
    levelFound = true;
    
    if (level == 0){
        return levelZero;
    }
    else{
        if (!level_tree.exists(level)){
            levelFound = false;
        }
        return (level_tree.getRank(level, level_rank, false));
    }

}
int Group::getTopPlayersStats(int num_of_players, LevelData &lower_stat, LevelData &higher_stat){
    LevelData *level_data;
    LevelTree::Iterator level_iter = level_tree.lastInOrder();
    if(*level_iter == nullptr){
        return 0;
    }
    int total_players = (*level_iter)->getSubPlayers();
    if(num_of_players > total_players){
        return -1;
    }
    
    int target_num_players = (*level_iter)->getSubPlayers() - num_of_players;
    lower_stat = level_tree.getLevelDataRank(num_of_players-1,0,dataFunc,true);
    higher_stat = level_iter;

//find the first node that level_sum - sub_tree_players < m
}


double Group::getPercentOfPlayersWithScoreInBounds(int score, int lowerLevel, int higherLevel, double * players){
    bool level_found = true;
    LevelData lower_rank = getRank(lowerLevel, level_found);
    LevelData higher_rank = getRank(higherLevel, level_found);
    
    double players_with_score = higher_rank.getScore()[score] - lower_rank.getScore()[score];
    double total_players = higher_rank.getSubPlayers() - lower_rank.getSubPlayers();
    return (players_with_score/total_players);
}
/*
void Group::AverageHighestPlayerLevel(int num_of_players, double *level){
    getTopPlayersStats(num_of_players,)
}
*/
void Group::GetPlayersBound(int score, int num_of_players, int *LowerBoundPlayers, int *HigherBoundPlayers){}

// =========================================================================== //
// ============================= Private Methods ============================= //
// =========================================================================== //

LevelData* Group::getLevelData(int level){
    if (level == 0){
        return &levelZero;
    }
    else{
        return level_tree.find(level);
    }
}
