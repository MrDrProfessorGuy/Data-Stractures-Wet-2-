#include "LevelData.h"
#include "assert.h"

LevelData::LevelData(int level): level(level),
                                level_sum(0), sub_tree_players(0){
    for(int i = 0; i < HIST_SIZE; i++) {
        score_hist[i] = 0;
    }
};

LevelData::LevelData(Player& player){
    level = player.level;
    //num_of_players = 1;
    level_sum = player.level;
    sub_tree_players = 1;
    for(int i = 0; i < HIST_SIZE; i++) {
        score_hist[i] = 0;
    }
    if (player.score < HIST_SIZE){
        score_hist[player.score] = 1;
    }
};


LevelData::LevelData(const LevelData& level_data): level(level_data.level),
                                    level_sum(level_data.level_sum), sub_tree_players(level_data.sub_tree_players){
    for(int i = 0; i < HIST_SIZE; i++) {
        score_hist[i] = level_data.score_hist[i];
    }
}

LevelData::~LevelData(){}

int LevelData::getLevel() const{
    return level;
}
int LevelData::getLevelSum() {
    return level_sum;
}
int LevelData::getSubPlayers(){
    return sub_tree_players;
}

int* LevelData::getScoreHist() {
    return score_hist;
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

void LevelData::setScoreHist(int *hist) {
    for(int i = 0; i < HIST_SIZE; i++){
        score_hist[i] = hist[i];
    }
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

// action = true - add
// action = false - subtraction
void LevelData::mergeSubLevelData(const LevelData& level_data, bool action) {
    if(action){
        level_sum += level_data.level_sum;
        sub_tree_players += level_data.sub_tree_players;
        for(int i = 0; i < HIST_SIZE; i++){
            score_hist[i] += level_data.score_hist[i];
        }
    }
    else{
        level_sum -= level_data.level_sum;
        sub_tree_players -= level_data.sub_tree_players;
    
        for(int i = 0; i < HIST_SIZE; i++){
            score_hist[i] -= level_data.score_hist[i];
            assert(score_hist[i] >= 0);
        }
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
    this->mergeSubLevelData(level_data, true);
    return *this;
}

LevelData& LevelData::operator-=(const LevelData& level_data){
    this->mergeSubLevelData(level_data, false);
    return *this;
}

LevelData operator-(const LevelData& level_data1, const LevelData& level_data2){
    LevelData new_level = LevelData(level_data1.getLevel());
    new_level.mergeSubLevelData(level_data1, true);
    new_level.mergeSubLevelData(level_data2, false);
    return new_level;
}

LevelData operator+(const LevelData& level_data1, const LevelData& level_data2){
    LevelData new_level = LevelData(level_data1.getLevel());
    new_level.mergeSubLevelData(level_data1, true);
    new_level.mergeSubLevelData(level_data2, true);
    return new_level;
}


void LevelData::swapSubTreeData(LevelData& level_data1, LevelData& level_data2){

    int tmp_level_sum = level_data1.getLevelSum();
    int tmp_STP = level_data1.getSubPlayers();
    
    int tmp_hist[HIST_SIZE];
    for(int i = 0; i < HIST_SIZE; i++){
        tmp_hist[i] = level_data1.score_hist[i];
    }
    
    level_data1.setLevelSum(level_data2.getLevelSum());
    level_data1.setSubTreePlayers(level_data2.getSubPlayers());
    level_data1.setScoreHist(level_data2.getScoreHist());
    
    level_data2.setLevelSum(tmp_level_sum);
    level_data2.setSubTreePlayers(tmp_STP);
    level_data2.setScoreHist(tmp_hist);
    
}

