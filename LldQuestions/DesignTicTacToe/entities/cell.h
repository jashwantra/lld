#ifndef cell_H
#define cell_H 1

#include "enums/symbol.h"

class Cell{
    private:
    Symbol symbol;
    public:
    Cell();
    Symbol getSymbol();
    void setSymbol(Symbol);
    
};

#endif