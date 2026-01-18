#ifndef board_H
#define board_H 1

#include "cell.h"
#include <vector>
#include <memory>
using namespace std;
class Board{
    private:
    int size;
    int movesCount;
    vector<vector<shared_ptr<Cell>>> board;
    public:
    Board(int);
    void initializeBoard() ;
    shared_ptr<Cell> getCell(int ,int);
    void placeSymbol(int,int, Symbol);
    bool isFull();
    int getSize();
    void printBoard();
};

#endif