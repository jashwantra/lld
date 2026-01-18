#include "rowWinningStrategy.h"

bool RowWinningStrategy :: checkWinner(shared_ptr<Board> board, shared_ptr<Player> player) {
    for(int i=0;i<board->getSize();i++){
        bool isWin = true;
        for(int j=0;j<board->getSize();j++){
            if(board->getCell(i,j)->getSymbol() != player->getSymbol()){
                isWin = false;
                break;
            }
        }
        if(isWin) return true;
    }
    return false;
}

