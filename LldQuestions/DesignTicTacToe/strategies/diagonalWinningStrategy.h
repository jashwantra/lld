#ifndef diagonalWinningStrategy_H
#define diagonalWinningStrategy_H 1

#include "winningStrategy.h"

class DiagonalWinningStrategy : public WinningStrategy{
    public:
    bool checkWinner(shared_ptr<Board> board, shared_ptr<Player> player) override;
};

#endif