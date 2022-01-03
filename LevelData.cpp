#include "LevelData.h"

LevelData::LevelData(int level): level(level), level_sum(), sub_tree_players() {};

LevelData::LevelData(const LevelData& level_data): level(level_data.level), level_sum(level_data.level_sum),
                    sub_tree_players(level_data.sub_tree_players){
    for(int i = 0; i < HIST_SIZE; i++) {
        score_hist[i] = level_data.score_hist[i];
    }
}

LevelData::~LevelData(){}

int LevelData::getLevel(){
    return level;
}

int LevelData::getLevelSum() {
    return level_sum;
}
int LevelData::getSubPlayers(){
    return sub_tree_players;
}

void LevelData::setLevel(int new_level){
    level = new_level;
}

void LevelData::setLevelSum(int new_level_sum){
    level_sum = new_level_sum;
}

void LevelData::setSubTreePlayers (int new_sub_tree_players){
    sub_tree_players = new_sub_tree_players;
}

void LevelData::addNewData(const Player& player){
    level_sum += player.level;
    sub_tree_players++;
    score_hist[player.score]++;
}
void LevelData::removeData(const Player& player){
    level_sum -= player.level;
    sub_tree_players--;
    score_hist[player.score]--;
}

void LevelData::mergeLevelData(const LevelData& level_data) {
    level_sum += level_data.level_sum;
    sub_tree_players += level_data.sub_tree_players;
    
    for(int i = 0; i < HIST_SIZE; i++){
        score_hist[i] += level_data.score_hist[i];
    }
}
// rewmove : action = false
// add : action = true
void LevelData::updateScore(int score, bool action){
    if(action){
        score_hist[score]++;
    }
    else {
        score_hist[score]--;
    }
}

bool LevelData::operator<(const LevelData& level_data) const{
    return level < level_data.level;
}

bool LevelData::operator>(const LevelData& level_data) const{
    return level > level_data.level;
}

bool LevelData::operator==(const LevelData& level_data) const{
    if(!(this->operator<(level_data)) && !(this->operator>(level_data))){
        return true;
    }
    return false;
}
bool LevelData::operator!=(const LevelData& level_data) const{
    if(!(this->operator==(level_data))){
        return true;
    }
    return false;
}

LevelData& LevelData::operator+=(const LevelData& level_data){
    this->mergeLevelData(level_data);
    return *this;
}
