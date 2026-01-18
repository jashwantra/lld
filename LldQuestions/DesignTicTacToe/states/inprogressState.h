#ifndef inProgressState_H
#define inProgressState_H 1

#include "gameState.h"

class InProgressState : public GameState {
    void handleMove(shared_ptr<Game> game, shared_ptr<Player> player, int row, int col) override ;
};

#endif