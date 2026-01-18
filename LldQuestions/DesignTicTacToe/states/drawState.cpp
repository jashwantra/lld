#include "drawState.h"
#include "exceptions/invalidMoveException.h"
void DrawState :: handleMove(shared_ptr<Game> game, shared_ptr<Player> player, int row, int col) {
    throw InvalidMoveException("Game is already over. It was a draw.");
}


