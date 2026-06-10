#include "Player.h"

Player::Player() {
    name = "玩家";
}

void Player::setName(std::string n) {
    name = n;
}

std::string Player::getName() {
    return name;
}
