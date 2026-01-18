#ifndef winningStrategy_H
#define winningStrategy_H 1

#include <memory>
#include "entities/board.h"
#include "entities/player.h"

class WinningStrategy{
    public:
    virtual ~WinningStrategy() = default;
    virtual bool checkWinner(shared_ptr<Board> board, shared_ptr<Player> player) = 0;
};

#endif