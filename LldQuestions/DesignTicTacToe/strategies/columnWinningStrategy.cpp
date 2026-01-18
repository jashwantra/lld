#include "columnWinningStrategy.h"

bool ColumnWinningStrategy :: checkWinner(shared_ptr<Board> board, shared_ptr<Player> player){
    for(int j=0;j<board->getSize();j++){
        bool isWin = true;
        for(int i=0;i<board->getSize();i++){
            if(board->getCell(i,j)->getSymbol() != player->getSymbol()){
                isWin = false;
                break;
            }
        }
        if(isWin) return true;
    }
    return false;
}

