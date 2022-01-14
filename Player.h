//
// Created by guy cohen on 30/12/2021.
//

#ifndef DATA_STRACTURES_WET_2_PLAYER_H
#define DATA_STRACTURES_WET_2_PLAYER_H


class Player {
private:

public:
    int id;
    int level;
    int score;
    int group_id;
    
    Player(int PlayerID, int GroupID, int score);
    Player(const Player&) = default;
    Player& operator=(const Player& player) = default;
    ~Player();
    
    void setScore(int new_score);
    void setLevel(int new_level);
    void setGroupID(int new_group);
    
    //void increaseScore(int amount);
    void increaseLevel(int amount);
    
    bool operator<(const Player& player) const;
    bool operator>(const Player& player) const;
    bool operator==(const Player& player) const;
    bool operator!=(const Player& player) const;
    
    
};


#endif //DATA_STRACTURES_WET_2_PLAYER_H
