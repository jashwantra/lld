#ifndef columnWinningStrategy_H
#define columnWinningStrategy_H 1

#include "winningStrategy.h"

class ColumnWinningStrategy : public WinningStrategy{
    public:
    bool checkWinner(shared_ptr<Board> board, shared_ptr<Player> player) override;
};

#endif