#ifndef rowWinningStrategy_H
#define rowWinningStrategy_H 1

#include "winningStrategy.h"

class RowWinningStrategy : public WinningStrategy{
    public:
    bool checkWinner(shared_ptr<Board> board, shared_ptr<Player> player) override;
};

#endif