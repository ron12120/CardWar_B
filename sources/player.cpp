#include "player.hpp"
using namespace ariel;

    Player::Player(string playerName)
    {
        this->name=playerName;
        this->sizestack=0;
        this->cardstaken=0;
    }
    Player::Player(){}
    int Player::stacksize(){return this->sizestack;}
    int Player::cardesTaken(){return this->cardstaken;}
    std::string Player::getname(){return this->name;}



