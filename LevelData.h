
#ifndef DATA_STRACTURES_WET_2_LEVELDATA_H
#define DATA_STRACTURES_WET_2_LEVELDATA_H

#include "Player.h"

#define HIST_SIZE 200
#define INVALID_LEVEL -1

class LevelData {
private:
    int level;
    int num_of_players;
    int level_sum;
    int sub_tree_players;
    int score_hist[HIST_SIZE];
    
public:

    LevelData(int level);
    LevelData(const LevelData& level_data);
    LevelData& operator=(const LevelData& level_data) = default;
    ~LevelData();
    
    int getLevel();
    int numOfPlayers();
    int getLevelSum();
    int getSubPlayers();
    int* getScoreHist();
    void setLevel(int new_level);
    void setLevelSum (int new_level_sum);
    void setNumOfPlayers(int num);
    void setSubTreePlayers (int new_sub_tree_players);
    void setScoreHist(int *score_hist);
    void addNewData(const Player& player);
    void removeData(const Player& player);
    void mergeLevelData(const LevelData& level_data, bool action);
    void updateScore(int score, bool action);
    
    void swapSubTreeData(LevelData& level_data1, LevelData& level_data2);
    
    bool operator<(const LevelData& level_data) const;
    bool operator>(const LevelData& level_data) const;
    bool operator==(const LevelData& level_data) const;
    bool operator!=(const LevelData& level_data) const;
    
    LevelData& operator+=(const LevelData& level_data);
    LevelData& operator-=(const LevelData& level_data);
  
};

LevelData operator+(const LevelData& level_data1, const LevelData& level_data2);
LevelData operator-(const LevelData& level_data1, const LevelData& level_data2);

#endif //DATA_STRACTURES_WET_2_LEVELDATA_H
