#include "Player.h"

Player::Player(int PlayerID, int GroupID, int score): id(PlayerID), level(0), score(score), group_id(GroupID){};

Player::~Player() {}

void Player::setScore(int new_score) {
    score = new_score;
}

void Player::setGroupID(int new_group){
    group_id = new_group;
}

void Player::increaseLevel(int amount) {
    level += amount;
}
/*
void Player::increaseScore(int amount) {
    score += amount;
}
*/
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
