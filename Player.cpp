#include "Player.h"

Player::Player(int id, int score, int level): id(id), score(score), level(level){};

Player::~Player() {}

void Player::setScore(int new_score) {
    score = new_score;
}
void Player::setLevel(int new_level) {
    level = new_level;
}

void Player::setGroupID(int new_group){
    group_id = new_group;
}

bool Player::operator<(const Player& player) const{
    return id < player.id;
}

bool Player::operator>(const Player& player) const{
    return id > player.id;
}

bool Player::operator==(const Player& player) const{
    if(!(this->operator<(player)) && !(this->operator>(player))){
        return true;
    }
    return false;
}

bool Player::operator!=(const Player& player) const{
    if(!(this->operator==(player))){
        return true;
    }
    return false;
}
