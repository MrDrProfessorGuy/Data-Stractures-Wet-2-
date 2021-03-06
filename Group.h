

#ifndef DATA_STRACTURES_WET_2_GROUP_H
#define DATA_STRACTURES_WET_2_GROUP_H

#include "LevelTree.h"
#include "LevelData.h"
#include "HashTable.h"



typedef enum {
    LEVEL_SUM = 0,
    SUB_TREE_PLAYERS = -1,
    SCORE_HIST = -2,
} RankType;

class Group {
private:
    LevelData getLevelData(int level);
    LevelData getGroupRank();

public:
    int id;
    LevelTree level_tree;
    HashTable players;
    LevelData levelZero;
    
    Group(int group_id);
    Group(const Group&) = delete;
    ~Group() = default;
    
    bool merge(Group& group);
    
    LevelData getRank(int level, bool& levelFound);
    bool getTopPlayersStats(int num_of_players, LevelData &Remainder, LevelData &Quotient);
    
    
    void setLevelTree(LevelTree& level_tree);
    void setLevelZero(LevelData& levelZero);
    void setPlayers(HashTable players);
    int getNumPlayers();
    void addPlayer(int player_id, int score, int level = 0);
    void addPlayer(Player player);
    void removePlayer(int player_id);
    
    void updatePlayerLevel(int player_id, int new_level);
    void updatePlayerScore(int player_id, int new_score);
    void updatePlayerGroup(int player_id, int group_id);
    
    double getPercentOfPlayersWithScoreInBounds(int score, int lowerLevel, int higherLevel);
    
    bool AverageHighestPlayerLevel(int num_of_players, double &level);
    
    bool GetPlayersBound(int score, int num_of_players, int *LowerBoundPlayers, int *HigherBoundPlayers);
    
    
};


#endif //DATA_STRACTURES_WET_2_GROUP_H
