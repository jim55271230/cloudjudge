#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;
public:
    Player();
    void setName(std::string n);
    std::string getName();
};

#endif // PLAYER_H#pragma once
