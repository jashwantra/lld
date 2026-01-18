#ifndef drawState_H
#define drawState_H 1

#include "gameState.h"

class DrawState : public GameState {
    void handleMove(shared_ptr<Game> game, shared_ptr<Player> player, int row, int col) override ;
};

#endif