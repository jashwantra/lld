#include "board.h"
#include "exceptions/invalidMoveException.h"
#include <iostream>
#include <vector>

using namespace std;

Board::Board(int size_) : size(size_), movesCount(0){
    board.resize(size_, vector<shared_ptr<Cell>>(size_, NULL));
    initializeBoard();
}
void Board::initializeBoard(){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            board[i][j] = make_shared<Cell>();
        }
    }
}

shared_ptr<Cell> Board::getCell(int row, int col){
    return board[row][col];
}

int Board::getSize(){
    return size;
}

void Board::placeSymbol(int row, int col, Symbol symbol){
    if (row < 0 || row >= size || col < 0 || col >= size) {
        throw InvalidMoveException("Invalid position: out of bounds.");
    }

    if (board[row][col]->getSymbol() != Symbol::EMPTY) {
        throw InvalidMoveException("Invalid position: cell is already occupied.");
    }
    
    board[row][col]->setSymbol(symbol);
    movesCount++;
}

bool Board::isFull(){
    return movesCount == size * size;
}

void Board::printBoard(){
    cout << "-------------" << endl;
    for(int i = 0; i < size; i++) {
        cout << "| ";
        for(int j = 0; j < size; j++) {
            Symbol symbol = board[i][j]->getSymbol();
            cout << getSymbolChar(symbol) << " | ";
        }
        cout << endl << "-------------" << endl;
    }
}
