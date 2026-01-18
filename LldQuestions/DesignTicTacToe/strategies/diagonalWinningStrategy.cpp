#include "diagonalWinningStrategy.h"

bool DiagonalWinningStrategy :: checkWinner(shared_ptr<Board> board, shared_ptr<Player> player) {
    bool isWin = true;
    
    for(int i=0;i<board->getSize();i++){
        if(board->getCell(i,i)->getSymbol() != player->getSymbol()){
            isWin = false;
            break;
        }
    }
    
    if(isWin) return true;

    for(int i=0;i<board->getSize();i++){
        if(board->getCell(i,board->getSize()-i-1)->getSymbol() != player->getSymbol()){
            isWin = false;
            break;
        }
    }

    return isWin;
}

