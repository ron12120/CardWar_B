#include <string>
#include <iostream>
#pragma once
namespace ariel {
    class Card{
        int value;
        std::string shape;
    public:
        Card(int value,std::string shape);
        int getvalue();
        std::string getshape();

    };
};