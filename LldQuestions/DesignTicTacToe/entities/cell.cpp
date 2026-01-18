#include "cell.h"

Cell::Cell() : symbol(Symbol::EMPTY){}

Symbol Cell::getSymbol(){
    return symbol ;
}

void Cell::setSymbol(Symbol symbol_){
    symbol = symbol_ ;
}
