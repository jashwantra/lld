#ifndef gameState_H
#define gameState_H 1

#include <memory>
#include "entities/player.h"
using namespace std;
class Game;
class GameState {
public:
    virtual ~GameState() = default;
    virtual void handleMove(shared_ptr<Game> game, shared_ptr<Player> player, int row, int col) = 0;
};

#endif