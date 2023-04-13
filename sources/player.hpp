#include <iostream>
#include <string>
#pragma once
using namespace std;
namespace ariel {
    class Player{
        int sizestack;
        int cardstaken;
        string name;
    public:
        Player(string);
        Player();
        int stacksize();
        int cardesTaken(); 
        string getname();
        void setsizestack(int stackS){this->sizestack=stackS;}
        void setcardstaken(int cardT){this->cardstaken=cardT;}
    };
};
