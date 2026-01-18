#ifndef player_H
#define player_H 1

#include "enums/symbol.h"
#include <string>
class Player{
    private:
    std::string playerName;
    Symbol symbol;
    public:
    Player(std::string, Symbol);
    std::string getName();
    Symbol getSymbol();
};

#endif