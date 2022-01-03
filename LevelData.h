//
// Created by guy cohen on 30/12/2021.
//

#ifndef DATA_STRACTURES_WET_2_LEVELDATA_H
#define DATA_STRACTURES_WET_2_LEVELDATA_H

#include "Player.h"

#define HIST_SIZE 200

class LevelData {
private:
    int level;
    int level_sum;
    int sub_tree_players;
    int score_hist[HIST_SIZE];
public:

    LevelData(int level);
    LevelData(const LevelData& level_data);
    LevelData& operator=(const LevelData& level_data) = default;
    ~LevelData();
    
    int getLevel();
    int getLevelSum();
    int getSubPlayers();
    int* getScore();
    void setLevel(int new_level);
    void setLevelSum (int new_level_sum);
    void setSubTreePlayers (int new_sub_tree_players);
    void addNewData(const Player& player);
    void removeData(const Player& player);
    void mergeLevelData(const LevelData& level_data);
    void updateScore(int score, bool action);
    
    bool operator<(const LevelData& level_data) const;
    bool operator>(const LevelData& level_data) const;
    bool operator==(const LevelData& level_data) const;
    bool operator!=(const LevelData& level_data) const;
    
    LevelData& operator+=(const LevelData& level_data);
    LevelData& operator-=(const LevelData& level_data);
    
};

LevelData& operator+(const LevelData& level_data1, const LevelData& level_data2);

#endif //DATA_STRACTURES_WET_2_LEVELDATA_H
