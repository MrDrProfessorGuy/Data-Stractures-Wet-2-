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

void Group::addPlayer(int player_id, int GroupID , int score){
    if (players.exists(player_id)){
        return;
    }
    
    Player new_player(player_id, GroupID, score);
    LevelData playerData(new_player);
    players.insert(new_player);
    levelZero += playerData;
}
void Group::addPlayer(Player player){
    if (players.exists(player.id)){
        return;
    }
    if (player.level > 0){
        players.insert(player);
        level_tree.insertPlayer(player);
    }
    else if (player.level == 0){
        addPlayer(player.id, player.group_id, player.score);
    }
}
void Group::removePlayer(int player_id){
    Player* player = players.findPlayer(player_id);
    if (player == nullptr){
        return;
    }
    if (player->level > 0){
        level_tree.removePlayer(*player);
    }
    else if (player->level == 0){
        LevelData playerData(*player);
        levelZero -= playerData;
    }
    players.remove(player_id);
}

void Group::updatePlayerLevel(int player_id, int amount){
    Player* player = players.findPlayer(player_id);
    if (player == nullptr){
        return;
    }
    
    if (player->level > 0){
        level_tree.removePlayer(*player);
        player->increaseLevel(amount);
        level_tree.insertPlayer(*player);
    }
    else if (player->level == 0){
        LevelData playerData(*player);
        levelZero -= playerData;
        player->increaseLevel(amount);
        level_tree.insertPlayer(*player);
    }
}
void Group::updatePlayerScore(int player_id, int amount){
    Player* player = players.findPlayer(player_id);
    if (player == nullptr){
        return;
    }
    if (player->level > 0){
        level_tree.removePlayer(*player);
        player->setScore(amount);
        level_tree.insertPlayer(*player);
    }
    else if (player->level == 0){
        LevelData playerData(*player);
        levelZero -= playerData;
        player->setScore(amount);
        playerData = LevelData(*player);
        levelZero += playerData;
    }
    
}

bool Group::merge(Group& group){
    // ===== merge hashTable =====
    int group_size = group.players.size;
    for (int index = 0; index < group_size; index++){
        SortedList<Player>::const_iterator iter = group.players.array[index].begin();
        SortedList<Player>::const_iterator end = group.players.array[index].end();
        while (iter != end){
            (*iter).setGroupID(id);
            addPlayer(*iter);
            iter++;
        }
    }
    //levelZero += group.levelZero;
    return true;
}

int dataFunc(LevelData& data){
    return data.getSubPlayers();
}

LevelData Group::getRank(int level, bool& levelFound){
    levelFound = true;
    
    if (level == 0){
        return levelZero;
    }
    else if (level > 0){
        if (!level_tree.exists(level)){
            levelFound = false;
        }
        LevelData data = (level_tree.getRank(level, false)) + levelZero;
        if (data.getLevel() == INVALID_LEVEL && levelZero.getSubPlayers() > 0){
            data = levelZero;
        }
        return data;
    }
    return LevelData(INVALID_LEVEL);
}

bool Group::getTopPlayersStats(int num_of_players, LevelData &Remainder, LevelData &Quotient){
    Remainder = LevelData(INVALID_LEVEL);
    LevelData higher_bound = getGroupRank();
    if(higher_bound.getLevel() == INVALID_LEVEL){
        return false;//Failure
    }
    
    int total_players = higher_bound.getSubPlayers();
    if(num_of_players > total_players){
        return false;//Failure
    }
    else if(num_of_players == total_players){
        Quotient = higher_bound;
        Quotient.setLevel(higher_bound.getLevel());
        return true;
    }
    
    int target_num_players = total_players - num_of_players;
    if (target_num_players <= levelZero.getSubPlayers()){
        Quotient = higher_bound - levelZero;
        Quotient.setLevel(higher_bound.getLevel());
        if (target_num_players != levelZero.getSubPlayers()){
            Remainder = levelZero;
        }
        return true;
    }
    
    target_num_players -= levelZero.getSubPlayers();
    higher_bound -= levelZero;
    LevelData lower_bound = level_tree.getLevelDataRank(target_num_players,dataFunc,false);
    
    if (lower_bound.getSubPlayers() == target_num_players){
        Quotient = higher_bound - lower_bound;
    }
    else{
        LevelTree::Iterator remainder_iter = level_tree.findIter(lower_bound.getLevel());
        if (lower_bound.getLevel() >= 0){
            remainder_iter++;
        }
        bool found;
        LevelData iterRank = getRank((*remainder_iter)->getLevel(), found) - levelZero;
    
        Quotient = higher_bound - iterRank;
        Remainder = iterRank - lower_bound;
        Remainder.setLevel(iterRank.getLevel());
    }
    
    Quotient.setLevel(higher_bound.getLevel());
    return true;//Success
}


double Group::getPercentOfPlayersWithScoreInBounds(int score, int lowerLevel, int higherLevel){
    bool level_found = true;
    LevelData lower_rank = getRank(lowerLevel-1, level_found);
    LevelData higher_rank = getRank(higherLevel, level_found);
    
    double players_with_score = higher_rank.getScoreHist()[score] - lower_rank.getScoreHist()[score];
    double total_players = higher_rank.getSubPlayers() - lower_rank.getSubPlayers();
    if (total_players == 0){
        return FAILURE;
    }
    return (players_with_score/total_players)*100.0;
}

bool Group::AverageHighestPlayerLevel(int num_of_players, double &level){
    LevelData remainder(INVALID_LEVEL);
    LevelData quotient(INVALID_LEVEL);
    if (!getTopPlayersStats(num_of_players, remainder, quotient)){
        return false;
    }
    double level_sum = 0;
    int remaining_players = num_of_players - quotient.getSubPlayers();
    if (remaining_players >= 0){
        level_sum = quotient.getLevelSum() + remaining_players*remainder.getLevel();
    }
    else{
        level_sum = quotient.getLevel()*num_of_players;
    }
    
    level = level_sum/num_of_players;
    return true;
}

bool Group::GetPlayersBound(int score, int num_of_players, int *LowerBoundPlayers, int *HigherBoundPlayers){
    
    LevelData remainder(INVALID_LEVEL);
    LevelData quotient(INVALID_LEVEL);
    if (!getTopPlayersStats(num_of_players, remainder, quotient)){
        return false;
    }
    
    int max_remainder = 0;
    int min_remainder = 0;
    int remaining_players = num_of_players - quotient.getSubPlayers();
    if (remaining_players > 0){
        max_remainder = remaining_players;
        if (remainder.getScoreHist()[score] < remaining_players){
            max_remainder = remainder.getScoreHist()[score];
        }
        if (remaining_players > remainder.getSubPlayers() - remainder.getScoreHist()[score]){
            min_remainder = remaining_players - (remainder.getSubPlayers() - remainder.getScoreHist()[score]);
        }
        *HigherBoundPlayers = quotient.getScoreHist()[score] + max_remainder;
        *LowerBoundPlayers = quotient.getScoreHist()[score] + min_remainder;
    }
    else{
        max_remainder = num_of_players;
        if (quotient.getScoreHist()[score] < num_of_players){
            max_remainder = quotient.getScoreHist()[score];
        }
        if (num_of_players > quotient.getSubPlayers() - quotient.getScoreHist()[score]){
            min_remainder = num_of_players - (quotient.getSubPlayers() - quotient.getScoreHist()[score]);
        }
        *HigherBoundPlayers = max_remainder;
        *LowerBoundPlayers = min_remainder;
    }
    
    return true;
}

// =========================================================================== //
// ============================= Private Methods ============================= //
// =========================================================================== //

LevelData Group::getLevelData(int level){
    if (level == 0){
        if (levelZero.getSubPlayers() == 0){
            return LevelData(INVALID_LEVEL);
        }
        return levelZero;
    }
    else{
        LevelData* data = level_tree.find(level);
        if (data != nullptr){
            *data += levelZero;
            return *data;
        }
        return getLevelData(0);
    }
}

LevelData Group::getGroupRank(){
    if (*level_tree.root() == nullptr){
        if (levelZero.getSubPlayers() > 0){
            return levelZero;
        }
        return LevelData(INVALID_LEVEL);
    }
    else{
        bool found;
        return (getRank((*(level_tree.lastInOrder()).getKey()), found));
    }
}