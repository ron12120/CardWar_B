#include "card.hpp"
#include <string>
#include <iostream>
using namespace ariel;
Card::Card(int value,std::string shape){
    this->value=value;
    this->shape=shape;
}
int Card::getvalue(){
    return this->value;
}
std::string Card::getshape(){
    return this->shape;
}



   