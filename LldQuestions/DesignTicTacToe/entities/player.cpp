#include "player.h"

using namespace std;

Player::Player(string playerName_ , Symbol symbol_) : playerName(playerName_), symbol(symbol_) {}

string Player::getName(){
    return playerName ;
}

Symbol Player::getSymbol(){
    return symbol;
}
