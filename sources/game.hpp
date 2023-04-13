#include "player.hpp"
#include "card.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#pragma once

namespace ariel {
    class Game{
    Player &player1;
    Player &player2;
    vector<Card> packet;
    stack<Card> packetp1;
    stack<Card> packetp2;
    string log;
    string lastTurn;
    double wins1,wins2,num_turns,count_draws;
    int draw_in_a_row;
    public:
   
        Game(Player &playerT1,Player &playerT2);
        //Game();
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        void drawturn();
        string valuec(int index);
        string stringLastTurn(int index,Card card_1,Card card_2,int val1,int val2);
    };
};